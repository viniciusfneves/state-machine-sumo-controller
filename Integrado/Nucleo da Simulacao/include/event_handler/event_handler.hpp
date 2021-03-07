#ifndef EVENT_HANDLER_HPP
#define EVENT_HANDLER_HPP

#include "../machine/main_machine.hpp"
#include "../events/events.hpp"
#include "../sensors/edge_sensor/edge_sensor.hpp"
#include "../sensors/opponent_sensor/opponent_sensor.hpp"
#include <communications/dynamic_data/send_data.hpp>
#include "../utilities/timeout_implementation/timeout.hpp"

// Responsável por processar informações e emitir eventos dinamicamente para a máquina
void processMachineEvents()
{
    if (anyEventOnQueue())
    {
        switch (eventToProcess())
        {
        case Event::Start:
            Core.process_event(Start{});
            break;

        case Event::Terminate:
            Core.process_event(Terminate{});
            break;

        case Event::Reset:
            Core.process_event(Reset{});
            break;
        
        case Event::SendRobotConfig:
            broadcastConfigurations();

        default:
            break;
        }
    }
    else if (isTimeoutActive())
    {
        if (millis() >= timeoutTime)
        {
            cancelTimeout();
            Core.process_event(Timeout{});
        }
    }
    else if (isOpponentDetected())
    {
        Core.process_event(OpponentDetected{});
    }
    else if (isEdgeDetected())
    {
        Core.process_event(EdgeDetected{});
    }
    else
    {
        Core.process_event(None{});
    }
}
#endif
