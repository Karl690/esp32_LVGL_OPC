#pragma once
#include "main.h"

#define STORAGE_ADDRESS_TOOLINFO  0x0
#define STORAGE_ADDRESS_SETTINGS  0x40
#define STORAGE_ADDRESS_SOAPSTRING 0x100
void storage_init();
bool storage_erase();
bool storage_read(uint32_t address, uint8_t* data, size_t len);
bool storage_write(uint32_t address, uint8_t* data, size_t len);