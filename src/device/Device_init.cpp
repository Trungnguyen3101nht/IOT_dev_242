#include "Device_init.h"

void Device_init(){
    // TaskLED_init();
    TaskTemperature_Humidity_init();
    TaskRGB_init();
    TaskRelay_init();
}