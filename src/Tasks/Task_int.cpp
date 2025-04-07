#include "Task_init.h"

void Task_init()
{
    // Initialize the tasks
    xTaskCreate(TaskWifi, "TaskWifi", 4096, NULL, 1, NULL);
    xTaskCreate(TaskCoreIOTControl, "TaskCoreIOTControl", 8192, NULL, 1, NULL);
}