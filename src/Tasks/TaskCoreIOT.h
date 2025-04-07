#include <globals.h>

extern WiFiClient espClient;
extern PubSubClient client;
void reconnect_core();
void callback(char *topic, byte *payload, unsigned int length);
void TaskCoreIOTControl(void *pvParameters);
void mqtt_init();