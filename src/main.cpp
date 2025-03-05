#include <globals.h>

void setup()
{
  Serial.begin(115200);

  Serial.println("\nStarting ESP32...");
  Serial.println("\nWiFi connected!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // Initialize device and tasks
  Device_init();
}

void loop()
{
  // OTA maybe

  Serial.println("Hello world!");
  delay(1000);
}