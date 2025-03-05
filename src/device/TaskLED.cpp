#include "TaskLED.h"


void TaskLEDControl(void *pvParameters) {
    pinMode(PIN_LED, OUTPUT); // Initialize LED pin
    int ledState = 0;
    while(1) {
      
      if (ledState == 0) {
        digitalWrite(PIN_LED, HIGH); // Turn ON LED
      } else {
        digitalWrite(PIN_LED, LOW); // Turn OFF LED
      }
      ledState = 1 - ledState;
      vTaskDelay(2000);
    }
  }

  void TaskLED_init()
{
    xTaskCreate(TaskLEDControl, "TaskLed", 4096, NULL, 2, NULL);
}