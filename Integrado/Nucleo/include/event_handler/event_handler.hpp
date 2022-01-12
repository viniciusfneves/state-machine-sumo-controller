#pragma once

#include "../event_handler/circular_buffer.hpp"
#include "../machine/main_machine.hpp"
#include "../utilities/timeout_implementation/timeout.hpp"

// Responsável por processar informações e emitir eventos dinamicamente para a máquina
void processMachineEvents() {
    if (anyEventOnQueue()) {
        // NÃO RETORNAR AQUI
        switch (eventToProcess()) {
            case Event::Start:
                Core.process_event(Start{});
                break;

            case Event::Disengage:
                Core.process_event(Disengage{});
                break;

            case Event::Arm:
                Core.process_event(Arm{});
                break;

            case Event::Controller:
                Core.process_event(Controller{});
                break;

            default:
                break;
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
        return;
    }
}
