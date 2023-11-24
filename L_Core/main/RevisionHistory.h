#pragma once

#define SYSTEMINFO "ESP32SC01-PLUS"
#define RevisionHeader ">Hy:L_Core:"
#define MajorStep      "1.026"
#define RevisionDate   "11/24/2023"
#define SYSTEMVERSION  MajorStep " " RevisionDate
#define CONNECTIONSTRING ">Hy:L_Core Rev " MajorStep ":" RevisionDate ":ESP32SC01 Plus:---:\n"   //"1.000:0:0:0:USB"

/* 
1.026 11/24/2023
    Implemented NVS read/write. it need to set SHARED_SPI1 in sdkconfig.
1.024 11/21/2023
    Added BLE C# project for testing

1.022 11/01/2023
    Added  bcode, tools, cmdprocess

1.021 10/23/2023
    BLE works between SC01 and TTYGO .
        - Added ble-client.
        - SC01 works on both Server and client mode.
*/