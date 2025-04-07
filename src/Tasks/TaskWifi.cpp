#include "TaskWifi.h"

void TaskWifi(void *pvParameters)
{
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(SSID);
  WiFi.begin(SSID, PASSWORD);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("\nWiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // Kiểm tra kết nối WiFi liên tục
  while (1)
  {
    if (WiFi.status() != WL_CONNECTED)
    {
      Serial.println("WiFi lost, reconnecting...");
      WiFi.disconnect();
      WiFi.begin(SSID, PASSWORD);

      while (WiFi.status() != WL_CONNECTED)
      {
        delay(1000);
        Serial.print(".");
      }
      Serial.println("\nWiFi reconnected");
      Serial.print("IP address: ");
      Serial.println(WiFi.localIP());
    }

    vTaskDelay(pdMS_TO_TICKS(5000));
  }
}

void wifi_init()
{
  xTaskCreate(TaskWifi, "TaskWifi", 4096, NULL, 1, NULL);
}
