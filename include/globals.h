#ifndef GLOBALS_H
#define GLOBALS_H

// include libraries
#include <Wire.h>
#include <WiFi.h>
#include <time.h>
#include <map>
#include <DHT20.h>
#include "LittleFS.h"
#include "SPIFFS.h"
#include <AsyncTCP.h>
#include <Arduino.h>
#include <ArduinoJson.h>
#include <PubSubClient.h>
#include <ESPAsyncWebServer.h>
#include <WiFiUdp.h>
#include <NTPClient.h>
#include <SoftwareSerial.h>
#include <TinyGPS++.h>
#include <Adafruit_NeoPixel.h>
#include <HardwareSerial.h>
#include <NimBLEDevice.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "../src/common/defines.h"

// devices
#include "../src/device/Device_init.h"

#endif