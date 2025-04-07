#include <globals.h>

void setup()
{
  Serial.begin(115200);

  Serial.println("\nStarting ESP32...");

  // while (WiFi.status() != WL_CONNECTED)
  // {
  //   delay(500);
  //   Serial.print(".");
  // }

  Serial.println("\nWiFi connected!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (!LittleFS.begin(true))
  {
    Serial.println("An Error has occurred while mounting LittleFS");
  }

  // Initialize device and tasks
  Task_init();
  Device_init();
  Connect_init();
}

void loop()
{
  // OTA maybe
}