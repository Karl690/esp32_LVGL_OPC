#include "storage.h"
#include "esp_partition.h"

const esp_partition_t *partition;
esp_partition_mmap_handle_t map_handle;
	
void storage_init()
{
	partition = esp_partition_find_first(ESP_PARTITION_TYPE_DATA, ESP_PARTITION_SUBTYPE_ANY, "storage");	
}

bool storage_erase()
{
	return esp_partition_erase_range(partition, 0, partition->size) == ESP_OK?true: false;
}

bool storage_read(uint32_t address, uint8_t* data, size_t len)
{
	return esp_partition_read(partition, address, data, len) == ESP_OK ? true : false;
}

bool storage_write(uint32_t address, uint8_t* data, size_t len)
{
	return esp_partition_write(partition, address, data, len) == ESP_OK ? true : false;
}
