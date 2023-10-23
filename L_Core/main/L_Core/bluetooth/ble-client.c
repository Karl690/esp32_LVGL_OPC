#include "main.h"
#include "ble.h"
#include "../ui/ui-bluetooth.h"
struct gattc_profile_inst {
	esp_gattc_cb_t gattc_cb;
	uint16_t gattc_if;
	uint16_t app_id;
	uint16_t conn_id;
	uint16_t service_start_handle;
	uint16_t service_end_handle;
	uint16_t char_handle;
	esp_bd_addr_t remote_bda;
};

static esp_gattc_char_elem_t *char_elem_result   = NULL;
static esp_gattc_descr_elem_t *descr_elem_result = NULL;


///Declare static functions
static void esp_gap_cb(esp_gap_ble_cb_event_t event, esp_ble_gap_cb_param_t *param);
static void esp_gattc_cb(esp_gattc_cb_event_t event, esp_gatt_if_t gattc_if, esp_ble_gattc_cb_param_t *param);
static void gattc_profile_event_handler(esp_gattc_cb_event_t event, esp_gatt_if_t gattc_if, esp_ble_gattc_cb_param_t *param);

/* One gatt-based profile one app_id and one gattc_if, this array will store the gattc_if returned by ESP_GATTS_REG_EVT */
static struct gattc_profile_inst gl_profile_tab[BLE_CLIENT_PROFILE_NUM] = {
	[BLE_CLIENT_PROFILE_APP_ID] = {
	.gattc_cb = gattc_profile_event_handler,
	.gattc_if = ESP_GATT_IF_NONE, /* Not get the gatt_if, so initial is ESP_GATT_IF_NONE */
},
};


/*
static esp_ble_scan_params_t ble_scan_params = {
	.scan_type = BLE_SCAN_TYPE_ACTIVE,
	.own_addr_type = BLE_ADDR_TYPE_PUBLIC,
	.scan_filter_policy = BLE_SCAN_FILTER_ALLOW_ALL,
	.scan_interval = 0x50,
	.scan_window = 0x30,
	.scan_duplicate = BLE_SCAN_DUPLICATE_DISABLE
};
*/

static esp_bt_uuid_t remote_filter_service_uuid = {
	.len = ESP_UUID_LEN_16,
	.uuid = { .uuid16 = SPP_SERVICE_UUID, },
};

static esp_bt_uuid_t remote_filter_char_uuid = {
	.len = ESP_UUID_LEN_16,
	.uuid = { .uuid16 = ESP_GATT_UUID_SPP_DATA_RECEIVE, },
};

static esp_bt_uuid_t notify_descr_uuid = {
	.len = ESP_UUID_LEN_16,
	.uuid = { .uuid16 = ESP_GATT_UUID_CHAR_CLIENT_CONFIG, },
};

uint8_t is_client_connect = 0;
uint16_t spp_client_conn_id = 0;
uint16_t spp_client_mtu_size = 23;
static uint16_t cmd = 0;
static uint16_t spp_srv_start_handle = 0;
static uint16_t spp_srv_end_handle = 0;
static uint16_t spp_gattc_if = 0xff;
static char * notify_value_p = NULL;
static int notify_value_offset = 0;
static int notify_value_count = 0;
static uint16_t count = SPP_IDX_NB;
static esp_gattc_db_elem_t *db = NULL;
static QueueHandle_t cmd_reg_queue = NULL;
QueueHandle_t spp_uart_queue = NULL;

static esp_bt_uuid_t spp_client_service_uuid = {
    .len  = ESP_UUID_LEN_16,
    .uuid = {.uuid16 = SPP_SERVICE_UUID},
};

static void esp_gattc_cb(esp_gattc_cb_event_t event, esp_gatt_if_t gattc_if, esp_ble_gattc_cb_param_t *param)
{
    /* If event is register event, store the gattc_if for each profile */
    if (event == ESP_GATTC_REG_EVT) {
        if (param->reg.status == ESP_GATT_OK) {
            ble_client_remote_device[param->reg.app_id].gattc_if = gattc_if;
             //gl_profile_tab[param->reg.app_id].gattc_if = gattc_if;
        } else {
            ESP_LOGI(BLE_TAG, "reg app failed, app_id %04x, status %d",
                    param->reg.app_id,
                    param->reg.status);
            return;
        }
    }

    /* If the gattc_if equal to profile A, call profile A cb handler,
     * so here call each profile's callback */
    do {
        int idx;
        for (idx = 0; idx < BLE_CLIENT_MAX_CONNECT_NUM; idx++) {
            if (gattc_if == ESP_GATT_IF_NONE || /* ESP_GATT_IF_NONE, not specify a certain gatt_if, need to call every profile cb function */
                    gattc_if == ble_client_remote_device[idx].gattc_if) {
                if (ble_client_remote_device[idx].gattc_cb) {
                    ble_client_remote_device[idx].gattc_cb(event, gattc_if, param);
                }
            }
        }
    } while (0);
}

static void gattc_profile_event_handler(esp_gattc_cb_event_t event, esp_gatt_if_t gattc_if, esp_ble_gattc_cb_param_t *param)
{
    esp_ble_gattc_cb_param_t *p_data = (esp_ble_gattc_cb_param_t *)param;
	BleRemoteDevice* dev = NULL;
    switch (event) {
    case ESP_GATTC_REG_EVT: 
	    break;
    case ESP_GATTC_CONNECT_EVT:
        break;
    case ESP_GATTC_OPEN_EVT:
        if (param->open.status != ESP_GATT_OK){
            ESP_LOGE(BLE_TAG, "open failed, status %d", p_data->open.status);
            break;
        }
	    dev = ble_client_get_device_by_address(p_data->open.remote_bda);	
	    if (dev) {
		    dev->conn_id = p_data->open.conn_id;
		    memcpy(dev->remote_bda, p_data->open.remote_bda, sizeof(esp_bd_addr_t));
	    }
	    esp_ble_gattc_search_service(gattc_if, param->open.conn_id, &remote_filter_service_uuid);
	    
	    dev->is_connected = 1;
	    ui_ble_set_device_status(dev);        
        break;    
    case ESP_GATTC_CFG_MTU_EVT:
	    //esp_ble_gattc_send_mtu_req(gattc_if, p_data->cfg_mtu.conn_id);
        break;
    case ESP_GATTC_SEARCH_RES_EVT: {        
        ESP_LOGI(BLE_TAG, "SEARCH RES: conn_id = %x is primary service %d", p_data->search_res.conn_id, p_data->search_res.is_primary);
        ESP_LOGI(BLE_TAG, "start handle %d end handle %d current handle value %d", p_data->search_res.start_handle, p_data->search_res.end_handle, p_data->search_res.srvc_id.inst_id);
	    dev = ble_client_get_device_by_conn_id(p_data->search_res.conn_id);	
        if (p_data->search_res.srvc_id.uuid.len == ESP_UUID_LEN_16 && p_data->search_res.srvc_id.uuid.uuid.uuid16 == SPP_SERVICE_UUID) {
            ESP_LOGI(BLE_TAG, "service found");
            dev->get_server = true;
            dev->service_start_handle = p_data->search_res.start_handle;
            dev->service_end_handle = p_data->search_res.end_handle;
            ESP_LOGI(BLE_TAG, "UUID16: %x", p_data->search_res.srvc_id.uuid.uuid.uuid16);
        }
        break;
    }
    case ESP_GATTC_SEARCH_CMPL_EVT:
	    esp_ble_gattc_send_mtu_req(gattc_if, p_data->search_cmpl.conn_id);
//        if (p_data->search_cmpl.status != ESP_GATT_OK){
//            ESP_LOGE(BLE_TAG, "search service failed, error status = %x", p_data->search_cmpl.status);
//            break;
//        }
//        if(p_data->search_cmpl.searched_service_source == ESP_GATT_SERVICE_FROM_REMOTE_DEVICE) {
//            ESP_LOGI(BLE_TAG, "Get service information from remote device");
//        } else if (p_data->search_cmpl.searched_service_source == ESP_GATT_SERVICE_FROM_NVS_FLASH) {
//            ESP_LOGI(BLE_TAG, "Get service information from flash");
//        } else {
//            ESP_LOGI(BLE_TAG, "unknown service source");
//        }
//        ESP_LOGI(BLE_TAG, "ESP_GATTC_SEARCH_CMPL_EVT");
//	    dev = ble_client_get_device_by_conn_id(p_data->search_cmpl.conn_id);	
//        if (dev->get_server){
//            uint16_t count = 0;
//            esp_gatt_status_t status = esp_ble_gattc_get_attr_count( gattc_if,
//                                                                     p_data->search_cmpl.conn_id,
//                                                                     ESP_GATT_DB_CHARACTERISTIC,
//                                                                     dev->service_start_handle,
//                                                                     dev->service_end_handle,
//                                                                     0,
//                                                                     &count);
//            if (status != ESP_GATT_OK){
//                ESP_LOGE(BLE_TAG, "esp_ble_gattc_get_attr_count error");
//            }
//
//            if (count > 0){
//                char_elem_result = (esp_gattc_char_elem_t *)malloc(sizeof(esp_gattc_char_elem_t) * count);
//                if (!char_elem_result){
//                    ESP_LOGE(BLE_TAG, "gattc no mem");
//                }else{
//                    status = esp_ble_gattc_get_char_by_uuid( gattc_if,
//                                                             p_data->search_cmpl.conn_id,
//                                                             dev->service_start_handle,
//                                                             dev->service_end_handle,
//                                                             remote_filter_char_uuid,
//                                                             char_elem_result,
//                                                             &count);
//                    if (status != ESP_GATT_OK){
//                        ESP_LOGE(BLE_TAG, "esp_ble_gattc_get_char_by_uuid error");
//                    }
//
//                    /*  Every service have only one char in our 'ESP_GATTS_DEMO' demo, so we used first 'char_elem_result' */
//                    if (count > 0 && (char_elem_result[0].properties & ESP_GATT_CHAR_PROP_BIT_NOTIFY)){
//                        dev->char_handle = char_elem_result[0].char_handle;
//                        esp_ble_gattc_register_for_notify (gattc_if, dev->remote_bda, char_elem_result[0].char_handle);
//                    }
//                }
//                /* free char_elem_result */
//                free(char_elem_result);
//            }else{
//                ESP_LOGE(BLE_TAG, "no char found");
//            }
//        }
         break;
    case ESP_GATTC_REG_FOR_NOTIFY_EVT: 
        ESP_LOGI(BLE_TAG, "ESP_GATTC_REG_FOR_NOTIFY_EVT");
	    dev = ble_client_get_device_by_address(p_data->connect.remote_bda);	
        if (p_data->reg_for_notify.status != ESP_GATT_OK){
            ESP_LOGE(BLE_TAG, "REG FOR NOTIFY failed: error status = %d", p_data->reg_for_notify.status);
        }else{
            uint16_t count = 0;
            uint16_t notify_en = 1;
            esp_gatt_status_t ret_status = esp_ble_gattc_get_attr_count( gattc_if,
                                                                         dev->conn_id,
                                                                         ESP_GATT_DB_DESCRIPTOR,
                                                                         dev->service_start_handle,
                                                                         dev->service_end_handle,
                                                                         dev->char_handle,
                                                                         &count);
            if (ret_status != ESP_GATT_OK){
                ESP_LOGE(BLE_TAG, "esp_ble_gattc_get_attr_count error");
            }
            if (count > 0){
                descr_elem_result = (esp_gattc_descr_elem_t*)malloc(sizeof(esp_gattc_descr_elem_t) * count);
                if (!descr_elem_result){
                    ESP_LOGE(BLE_TAG, "malloc error, gattc no mem");
                }else{
                    ret_status = esp_ble_gattc_get_descr_by_char_handle( gattc_if,
                                                                         dev->conn_id,
                                                                         p_data->reg_for_notify.handle,
                                                                         notify_descr_uuid,
                                                                         descr_elem_result,
                                                                         &count);
                    if (ret_status != ESP_GATT_OK){
                        ESP_LOGE(BLE_TAG, "esp_ble_gattc_get_descr_by_char_handle error");
                    }
                    /* Every char has only one descriptor in our 'ESP_GATTS_DEMO' demo, so we used first 'descr_elem_result' */
                    if (count > 0 && descr_elem_result[0].uuid.len == ESP_UUID_LEN_16 && descr_elem_result[0].uuid.uuid.uuid16 == ESP_GATT_UUID_CHAR_CLIENT_CONFIG){
	                    ret_status = (esp_gatt_status_t)esp_ble_gattc_write_char_descr( gattc_if,
                                                                     dev->conn_id,
                                                                     descr_elem_result[0].handle,
                                                                     sizeof(notify_en),
                                                                     (uint8_t *)&notify_en,
                                                                     ESP_GATT_WRITE_TYPE_RSP,
                                                                     ESP_GATT_AUTH_REQ_NONE);
                    }

                    if (ret_status != ESP_GATT_OK){
                        ESP_LOGE(BLE_TAG, "esp_ble_gattc_write_char_descr error");
                    }

                    /* free descr_elem_result */
                    free(descr_elem_result);
                }
            }
            else{
                ESP_LOGE(BLE_TAG, "decsr not found");
            }

        }
        break;
    case ESP_GATTC_NOTIFY_EVT:
        if (p_data->notify.is_notify){
            ESP_LOGI(BLE_TAG, "ESP_GATTC_NOTIFY_EVT, receive notify value:");
        }else{
            ESP_LOGI(BLE_TAG, "ESP_GATTC_NOTIFY_EVT, receive indicate value:");
        }
        esp_log_buffer_hex(BLE_TAG, p_data->notify.value, p_data->notify.value_len);
        break;
    case ESP_GATTC_WRITE_DESCR_EVT:
        if (p_data->write.status != ESP_GATT_OK){
            ESP_LOGE(BLE_TAG, "write descr failed, error status = %x", p_data->write.status);
            break;
        }
        ESP_LOGI(BLE_TAG, "write descr success ");
        uint8_t write_char_data[35];
	    dev = ble_client_get_device_by_address(p_data->connect.remote_bda);	
        for (int i = 0; i < sizeof(write_char_data); ++i)
        {
            write_char_data[i] = i % 256;
        }
        esp_ble_gattc_write_char( gattc_if,
                                  dev->conn_id,
                                  dev->char_handle,
                                  sizeof(write_char_data),
                                  write_char_data,
                                  ESP_GATT_WRITE_TYPE_RSP,
                                  ESP_GATT_AUTH_REQ_NONE);
        break;
    case ESP_GATTC_SRVC_CHG_EVT: {
        esp_bd_addr_t bda;
        memcpy(bda, p_data->srvc_chg.remote_bda, sizeof(esp_bd_addr_t));
        ESP_LOGI(BLE_TAG, "ESP_GATTC_SRVC_CHG_EVT, bd_addr:");
        esp_log_buffer_hex(BLE_TAG, bda, sizeof(esp_bd_addr_t));
        break;
    }
    case ESP_GATTC_WRITE_CHAR_EVT:
        if (p_data->write.status != ESP_GATT_OK){
            ESP_LOGE(BLE_TAG, "write char failed, error status = %x", p_data->write.status);
            break;
        }
        ESP_LOGI(BLE_TAG, "write char success ");
        break;
    case ESP_GATTC_DISCONNECT_EVT:
	    dev = ble_client_get_device_by_address(p_data->disconnect.remote_bda);	
	    if (!dev) break;
        dev->is_connected = 0;
        dev->get_server = 0;
        ESP_LOGI(BLE_TAG, "ESP_GATTC_DISCONNECT_EVT, reason = %d", p_data->disconnect.reason);
        ui_ble_set_device_status(dev);
        break;
    default:
        break;
    }
}

uint8_t ble_client_enable()
{
    esp_err_t status;
	char err_msg[20];
	
    //register the callback function to the gattc module
    if ((status = esp_ble_gattc_register_callback(esp_gattc_cb)) != ESP_OK) {
        ESP_LOGE(BLE_TAG, "gattc register error: %s", esp_err_to_name_r(status, err_msg, sizeof(err_msg)));
        return 0;
    }
	
	for (uint8_t i = 0; i < BLE_CLIENT_MAX_CONNECT_NUM; i++) {
		ble_client_remote_device[i].gattc_cb = gattc_profile_event_handler;
		ble_client_remote_device[i].gattc_if = ESP_GATT_IF_NONE;
		status = esp_ble_gattc_app_register(i);
		if (status != ESP_OK)
		{
			ESP_LOGE(BLE_TAG, "%s gattc app register failed, error code = %x\n", __func__, status);
		}
	}

    esp_err_t local_mtu_ret = esp_ble_gatt_set_local_mtu(200);
    if (local_mtu_ret){
        ESP_LOGE(BLE_TAG, "set local  MTU failed: %s", esp_err_to_name_r(local_mtu_ret, err_msg, sizeof(err_msg)));
    }
    
	return 1;
}


void ble_client_disable()
{
    for(uint8_t i = 0; i < BLE_CLIENT_MAX_CONNECT_NUM; i ++)
        esp_ble_gattc_app_unregister(i);
}
uint8_t ble_client_connect_device(BleRemoteDevice* dev) {
	return esp_ble_gattc_open(dev->gattc_if, dev->scan_result.scan_rst.bda, dev->scan_result.scan_rst.ble_addr_type, true) == ESP_OK;
}

void ble_client_disconnect_device(BleRemoteDevice* dev)
{
	esp_ble_gattc_close(dev->gattc_if, dev->conn_id);
}

void ble_client_write_data(BleRemoteDevice* dev, uint8_t* data, uint16_t len)
{
	esp_ble_gattc_write_char( dev->gattc_if,
		dev->conn_id,
		dev->char_handle,
		len,
		data,
		ESP_GATT_WRITE_TYPE_RSP,
		ESP_GATT_AUTH_REQ_NONE);
}