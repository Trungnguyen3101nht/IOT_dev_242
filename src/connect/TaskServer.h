#ifndef INC_TASKCONNECT_H_
#define INC_TASKCONNECT_H_

#include <globals.h>
extern AsyncWebServer server;
extern AsyncWebSocket ws;

void Task_connect_init();

void connnectWSV();

#endif // INC_TASKCONNECT_H_