#include "TaskHumiTemp.h"

double temperature = 0, humidity = 0;

void saveTemp_HumiToFile()
{
  File file = LittleFS.open("/temp_humi.dat", "a");
  if (!file)
  {
    Serial.println("Failed to open file for appending");
    return;
  }

  DynamicJsonDocument doc(2048);
  doc["mode"] = "Temp_Humi";
  doc["data"] = String(temperature, 2) + "-" + String(humidity, 2);

  if (file.size() > 0)
  {
    file.print(",\n");
  }

  if (serializeJson(doc, file) == 0)
  {
    Serial.println("Failed to write to file");
  }

  file.close();
}
void TaskTemperature_Humidity(void *pvParameters)
{
  DHT20 dht20;
  Wire.begin(GPIO_NUM_11, GPIO_NUM_12);
  dht20.begin();
  Serial.println("Task Temperature and Humidity");
  while (1)
  {

    dht20.read();
    temperature = dht20.getTemperature();
    humidity = dht20.getHumidity();

    // Serial.print("Temp: ");
    // Serial.print(temperature);
    // Serial.print(" *C ");
    // Serial.print(" Humi: ");
    // Serial.print(humidity);
    // Serial.print(" %");
    // Serial.println();

    String data = "{";
    data += "\"temperature\":" + String(dht20.getTemperature()) + ",";
    data += "\"humidity\":" + String(dht20.getHumidity());
    data += "}";

    DynamicJsonDocument doc(256);
    doc["temperature"] = temperature;
    doc["humidity"] = humidity;

    String jsonData;
    serializeJson(doc, jsonData);

    // Gửi dữ liệu đến tất cả WebSocket client
    ws.textAll(jsonData);

    client.publish("v1/devices/me/telemetry", data.c_str());
    if (WiFi.status() != WL_CONNECTED)
    {
      if (temperature != 0 && humidity != 0)
      {
        saveTemp_HumiToFile();
      }
    }
    vTaskDelay(5000);
  }
}

void TaskTemperature_Humidity_init()
{
  xTaskCreate(TaskTemperature_Humidity, "TaskTemperature_Humidity", 2048, NULL, 2, NULL);
}