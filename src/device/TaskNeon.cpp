#include "TaskNeon.h"

Adafruit_NeoPixel led_rgb(NUM_PIXELS, PIN_NEON, NEO_GRB + NEO_KHZ800);

void TaskRGB(void *pvParameters)
{
    led_rgb.begin();
    led_rgb.show();
    bool ledState = false;

    while (true)
    {
        if (WiFi.status() == WL_CONNECTED && client.connected())
        {
            // connecte to mqtt
            if (client.connected())
            {
                if (ledState)
                {
#ifdef IS_ROOT
                    led_rgb.setPixelColor(0, led_rgb.Color(0, 255, 200));
#else
                    led_rgb.setPixelColor(0, led_rgb.Color(255, 0, 0));
#endif
                }
                else
                {
                    led_rgb.setPixelColor(0, led_rgb.Color(0, 0, 0));
                }
            }
            else if (!client.connected())
            {
                if (ledState)
                {
#ifdef IS_ROOT
                    led_rgb.setPixelColor(0, led_rgb.Color(255, 0, 255));
#else
                    led_rgb.setPixelColor(0, led_rgb.Color(165, 255, 0));
#endif
                }
                else
                {
                    led_rgb.setPixelColor(0, led_rgb.Color(0, 0, 0));
                }
            }

            led_rgb.setBrightness(Brightness);
            led_rgb.show();
            ledState = !ledState;
        }
        // connecte to wifi
        if (WiFi.status() != WL_CONNECTED)
        {
            if (ledState)
            {
#ifdef IS_ROOT
                led_rgb.setPixelColor(0, led_rgb.Color(255, 0, 0));
#else
                led_rgb.setPixelColor(0, led_rgb.Color(0, 255, 0));
#endif
            }
            else
            {
                led_rgb.setPixelColor(0, led_rgb.Color(0, 0, 0));
            }
            led_rgb.show();
            ledState = !ledState;
        }
        vTaskDelay(delay_led / portTICK_PERIOD_MS);
    }
}

void TaskRGB_init()
{
    xTaskCreate(TaskRGB, "TaskRGB", 4096, NULL, 2, NULL);
}
