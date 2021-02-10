#include <machine/machine.hpp>
#include <events/events.hpp>
#include <Arduino.h>



void setup() {
    Serial.begin(115200);
}

void loop() {
    Core.process_event(Start{});
    delay(2000);
    Core.process_event(Timeout{});
    delay(2000);
    Core.process_event(Terminate{});
    delay(2000);
    Core.process_event(Reset{});
    delay(500);
}