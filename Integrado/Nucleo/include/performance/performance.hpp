#pragma once

struct PerformanceGauges {
    int64_t startTimestamp;
    int64_t timeToExecute;
    int numberOfTaks;
    uint32_t freeMemory;
    uint16_t stackWaterMark;

    void measure(int64_t actualTimestamp, uint8_t tasks, uint32_t heap, uint16_t stackWM) {
        timeToExecute = actualTimestamp - startTimestamp;
        numberOfTaks = tasks;
        freeMemory = heap;
        stackWaterMark = stackWM;
    }

    void measure(int64_t actualTimestamp) {
        timeToExecute = actualTimestamp - startTimestamp;
    }
};

PerformanceGauges performance;