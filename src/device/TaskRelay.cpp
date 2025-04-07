#include "TaskRelay.h"

QueueHandle_t ledQueue;
std::map<int, bool> relayStates;

void sendRelayState(int relayID, bool state)
{
    // Nếu trạng thái không thay đổi thì không gửi
    if (relayStates[relayID] == state)
        return;

    relayStates[relayID] = state; // Cập nhật trạng thái

    // Gửi JSON trạng thái mới qua WebSocket
    DynamicJsonDocument response(128);
    response["relayID"] = relayID;
    response["state"] = state;

    String responseMessage;

    serializeJson(response, responseMessage);
    if (ws.count() > 0)
    {
        ws.textAll(responseMessage);
    }
    // Serial.printf("Relay %d -> %s (Updated & Sent)\n", relayID, state ? "ON" : "OFF");
}
void onWebSocketEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len)
{
    if (type == WS_EVT_CONNECT)
    {
        Serial.printf("WebSocket client #%u connected\n", client->id());

        // Gửi trạng thái hiện tại của tất cả relay khi có client mới kết nối
        for (const auto &relay : relayStates)
        {
            sendRelayState(relay.first, relay.second);
        }
    }
    else if (type == WS_EVT_DISCONNECT)
    {
        Serial.printf("WebSocket client #%u disconnected\n", client->id());
    }
}

void updateRelayState(int relayID, bool state)
{
    sendRelayState(relayID, state);
}

void callback_relay(char *topic, byte *payload, unsigned int length)
{

    String message = "";
    for (int i = 0; i < length; i++)
    {
        message += (char)payload[i];
    }

    Serial.print("Extracted JSON: ");
    Serial.println(message);

    // Parse JSON
    JsonDocument doc;
    DeserializationError error = deserializeJson(doc, message);

    if (error)
    {
        Serial.print("JSON parsing failed: ");
        Serial.println(error.f_str());
        return;
    }

    // Lấy dữ liệu từ JSON
    String method = doc["method"].as<String>();
    bool state = doc["params"].as<bool>();

    // Kiểm tra method đúng không
    if (method.startsWith("setRelay"))
    {
        int relayID = method.substring(8).toInt();

        Serial.print("Extracted Relay ID: ");
        Serial.println(relayID);

        if (relayID > 0 && relayID <= 100)
        {
            int relayPin = relayID;
            pinMode(relayPin, OUTPUT);
            digitalWrite(relayPin, state ? HIGH : LOW);

            Serial.print(relayID);
            Serial.print(" - ");
            Serial.println(state ? "ON" : "OFF");
        }
        else
        {
            Serial.println("Invalid Relay ID!");
        }
    }
}

void TaskRelayControl(void *pvParameters)
{
    client.setServer(MQTT_SERVER, MQTT_PORT);
    client.setCallback(callback_relay);
    bool state;
    while (1)
    {
        if (xQueueReceive(ledQueue, &state, portMAX_DELAY))
        {
            digitalWrite(PIN_RELAY, state ? HIGH : LOW);
        }
        vTaskDelay(delay_relay);
    }
}

void TaskRelay_init()
{
    ledQueue = xQueueCreate(10, sizeof(bool)); // Tạo queue với 10 slot
    xTaskCreate(TaskRelayControl, "TaskRelayControl", 4096, NULL, 1, NULL);
    ws.onEvent(onWebSocketEvent);
}
