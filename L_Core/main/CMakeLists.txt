idf_component_register(
                SRCS
                	main.c
                	L_Core/ui/ui.c
                	L_Core/ui/ui_helpers.c
                	L_Core/open62541/open62541.c
                	L_Core/wifi/wifi.c
                	L_Core/open62541/opc.c
                	L_Core/ui/images/hyrel-mark.c
                	L_Core/ui/images/img-splash.c
                	L_Core/devices/display.c
                	K_Core/K_Core.c
                	K_Core/gpio/GPIO.c
                	K_Core/taskmanager.c
                	K_Core/gpio/GPIO.c
                	K_Core/K_Core.c
                	K_Core/taskmanager.c
                	K_Core/display/DisplayList.c
                	L_Core/ui/ui-opc.c
                	L_Core/ui/ui-main.c
                	K_Core/adc/adc.c
                INCLUDE_DIRS "."
                REQUIRES
                	LovyanGFX
                	lvgl
                	app_update
                	esp_https_ota
                	esp_event
                	esp_timer
                	spi_flash
                	esp_wifi
                	esp_partition
                	esp_hw_support)
component_compile_options(-fexceptions -x c++)
set_property(TARGET ${COMPONENT_TARGET} PROPERTY CXX_STANDARD 17)
