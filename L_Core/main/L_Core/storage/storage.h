#pragma once
#include "main.h"

#define STORAGE_ADDRESS_SETTINGS  0x0
#define STORAGE_ADDRESS_TOOLINFO  0x1000
#define STORAGE_ADDRESS_SOAPSTRING 0x2000
void storage_init();
bool storage_erase();
bool storage_read(uint32_t address, void* data, size_t len);
bool storage_write(uint32_t address, void* data, size_t len);