#pragma once

#define SYSTEMINFO "ESP32SC01-PLUS"
#define RevisionHeader ">Hy:L_Core:"
#define MajorStep      "1.021"
#define RevisionDate   "10/23/2023"
#define SYSTEMVERSION  MajorStep " " RevisionDate
#define CONNECTIONSTRING ">Hy:L_Core Rev " MajorStep ":" RevisionDate ":ESP32SC01 Plus:---:"   //"1.000:0:0:0:USB"

/* 
1.021 10/23/2023
    BLE works between SC01 and TTYGO .
        - Added ble-client.
        - SC01 works on both Server and client mode.
*/