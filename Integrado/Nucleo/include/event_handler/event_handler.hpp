#ifndef EVENT_HANDLER_HPP
#define EVENT_HANDLER_HPP

#include "../machine/main_machine.hpp"
#include "../event_handler/circular_buffer.hpp"
#include "../utilities/timeout_implementation/timeout.hpp"
#include "../utilities/timeout_implementation/telemetry_interval_timeout.hpp"
#ifdef ESP32_ENV
#include <communications/data/send_data.hpp>
#endif

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

        case Event::Controller:
            Core.process_event(Controller{});
            break;
#ifdef ESP32_ENV
        case Event::BroadcastRobotConfiguration:
            broadcastRobotConfiguration();
            setTelemetryBroadcast();

        case Event::BroadcastTelemetryData:
            broadcastTelemetryData(
                robotData.opponentSensorsDetectionArray,
                robotData.edgeSensorsDetectionArray,
                robotData.motorsPower);
            updateTelemetry();
#endif
        default:
            break;
        }
    }
    if (isTelemetryActive())
    {
        if (readToSend(millis()))
        {
            addEventToQueue(Event::BroadcastTelemetryData);
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
        if (getErrorFromOPSensors() == 0) {
            Core.process_event(OpponentInFront{});
        } else {
            Core.process_event(OpponentDetectedNotInFront{});
        }
        Core.process_event(OpponentDetected{});
        return;
    } else {
        if (getErrorFromOPSensors() < 0) {
            Core.process_event(LostOpponentAtLeft{});
        } else if (getErrorFromOPSensors() > 0) {
            Core.process_event(LostOpponentAtRight{});
        }
        
        Core.process_event(NotOpponentDetected{});
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
