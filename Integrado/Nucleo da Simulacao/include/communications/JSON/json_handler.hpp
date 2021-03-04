#if !defined(JSON_HANDLER)
#define JSON_HANDLER

#include "json_object.hpp"
#include <configuration/config_robot.hpp>

void deserializeJSON(String json)
{
    DeserializationError error = deserializeJson(doc, json);
    if (error)
    {
        Serial.print("deserializeJson() failed: ");
        Serial.println(error.f_str());
    }
}

// Lida com os dados recebidos do browser pelo WebSocket
void handleWSIncomingData(uint8_t client_id, WStype_t type, uint8_t *data, size_t length)
{
    switch (type)
    {
    case WStype_ERROR:
        Serial.printf("Client id (%u) -> ERROR\n", client_id);
        break;
    case WStype_DISCONNECTED:
        Serial.printf("Client id (%u) -> Disconnecting\n", client_id);
        break;
    case WStype_CONNECTED:
        Serial.printf("Client Connected! Assigned ID: %u\n", client_id);
        break;
    case WStype_TEXT:
        Serial.printf("JSON recieved from Id: %u\n", client_id);
        deserializeJSON(String((char *)data));
        reConfigureRobotFromComm();
        break;
    }
}
#endif // JSON_HANDLER
