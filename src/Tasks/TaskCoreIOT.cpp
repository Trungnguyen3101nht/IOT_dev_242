#include "TaskCoreIOT.h"
WiFiClient espClient;
PubSubClient client(espClient);
void reconnect_core()
{
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.println("Waiting for WiFi...");
    delay(1000);
  }
  printf("Waiting for WiFi...");
  while (!client.connected())
  {
    Serial.print("Attempting MQTT connection...");
    client.connect(CLIENT_ID, ACCESS_USERNAME, ACCESS_TOKEN);
    if (client.state() == 0)
    {
      Serial.println("Connected!");
      client.subscribe("v1/devices/me/rpc/request/+");
    }
    else
    {
      Serial.print("Failed, rc=");
      Serial.print(client.state());
      Serial.println(" --> Retry in 5s");
      delay(5000);
    }
  }
}

void callback(char *topic, byte *payload, unsigned int length)
{
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");

  String message = "";
  for (int i = 0; i < length; i++)
  {
    message += (char)payload[i];
  }
  Serial.println(message);

  if (message.indexOf("setValue") != -1)
  {
    client.publish("v1/devices/me/attributes", "{\"value\": true}");
  }
}

void TaskCoreIOTControl(void *pvParameters)
{
  client.setServer(MQTT_SERVER, MQTT_PORT);
  client.setCallback(callback);

  while (1)
  {
    if (WiFi.status() == WL_CONNECTED)
    {
      if (!client.connected())
      {
        reconnect_core();
      }
      client.loop();
    }
    vTaskDelay(delay_connect);
  }
}

void mqtt_init()
{
  xTaskCreate(TaskCoreIOTControl, "TaskCoreIOTControl", 8192, NULL, 2, NULL);
}