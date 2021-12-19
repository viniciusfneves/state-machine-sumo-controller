#ifndef EVENT_HANDLER_HPP
#define EVENT_HANDLER_HPP

#include "../event_handler/circular_buffer.hpp"
#include "../machine/main_machine.hpp"
#include "../utilities/timeout_implementation/telemetry_interval_timeout.hpp"
#include "../utilities/timeout_implementation/timeout.hpp"
#ifdef ESP32_ENV
#include <communications/data/send_data.hpp>
#endif

// Responsável por processar informações e emitir eventos dinamicamente para a máquina
void processMachineEvents() {
    if (anyEventOnQueue()) {
        // NÃO RETORNAR AQUI
        switch (eventToProcess()) {
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
            case Event::SetUpClient:
                broadcastRobotInfos();
                broadcastRobotConfiguration();
                setTelemetryBroadcast();
                break;

            case Event::BroadcastRobotConfiguration:
                broadcastRobotConfiguration();
                break;

            case Event::BroadcastTelemetryData:
                broadcastTelemetryData(
                    robotData.opponentSensorsDetectionArray,
                    robotData.edgeSensorsDetectionArray,
                    robotData.motorsPower);
                updateTelemetry();
                break;
#endif
            default:
                break;
        }
    }
    if (isTelemetryActive()) {
        // NÃO RETORNAR AQUI
        if (readToSend(millis())) {
            addEventToQueue(Event::BroadcastTelemetryData);
        }
    }
    if (isTimeoutActive()) {
        // NÃO RETORNAR AQUI
        if (timeoutAllowed(millis())) {
            cancelTimeout();
            Core.process_event(Timeout{});
        }
    }
    if (isOpponentDetected()) {
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
    if (isEdgeDetected()) {
        Core.process_event(EdgeDetected{});
        return;
    } else {
        Core.process_event(None{});
    }
}
#endif
