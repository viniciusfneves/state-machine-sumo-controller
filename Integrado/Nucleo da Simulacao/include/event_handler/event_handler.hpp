#ifndef EVENT_HANDLER_HPP
#define EVENT_HANDLER_HPP

#include "../machine/main_machine.hpp"
#include "../event_handler/circular_buffer.hpp"
#include "../sensors/sensors.hpp"
#include "../utilities/timeout_implementation/timeout.hpp"
#ifdef ESP32_ENV
#include <communications/dynamic_data/send_data.hpp>
#endif

// Responsável por processar informações e emitir eventos dinamicamente para a máquina
void processMachineEvents()
{
    readSensors();

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
#ifdef ESP32_ENV
        case Event::SendRobotConfig:
            broadcastConfigurations();
            broadcastMotorsPower(0, 0);
#endif
        default:
            break;
        }
    }
    if (isTimeoutActive())
    {
        if (millis() >= timeoutTime)
        {
            cancelTimeout();
            Core.process_event(Timeout{});
            return;
        }
    }
    if (isOpponentDetected())
    {
        Core.process_event(OpponentDetected{});
        return;
    }
    if (isEdgeDetected())
    {
        Core.process_event(EdgeDetected{});
        return;
    }
    else
    {
        Core.process_event(None{});
    }
}
#endif
