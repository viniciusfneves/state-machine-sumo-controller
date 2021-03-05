#if !defined(WEBSOCKETS_FUNCTIONS_HPP)
#define WEBSOCKETS_FUNCTIONS_HPP

#include "webSockets_server.hpp"

void trowRobotConfigurationData()
{
    String payload = "{ \"robot_name\" : \"Atena\", \"configurations\" : {\"initial_move\":\"none\",\"search\":\"none\",\"chase\":\"standard\"}}";
    // READINGS , {\"readings\" : {\"opponent_sensor\": [false,false,false,false,false], \"edge_sensor\":[false, false], \"motors_pwm\":[255,255]} 
    webSocket.broadcastTXT(payload);
}


#endif // WEBSOCKETS_FUNCTIONS_HPP
