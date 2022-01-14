#pragma once

struct PerformanceGauges {
    int64_t startTimestamp;  //us
    int64_t timeToExecute;   //us
    int numberOfTaks;
    uint32_t freeMemory;      // bytes
    uint16_t stackSize;       // bytes
    uint16_t stackWaterMark;  // bytes
    uint16_t BstackMaxUsage;  // bytes

    void setStackSize(uint8_t size) {
        stackSize = size;
    }

    void measure(int64_t actualTimestamp, uint8_t tasks, uint32_t heap, uint16_t stackWM) {
        timeToExecute = actualTimestamp - startTimestamp;
        numberOfTaks = tasks;
        freeMemory = heap;
        stackWaterMark = stackWM;
        BstackMaxUsage = stackSize - stackWaterMark;
    }

    void measure(int64_t actualTimestamp) {
        timeToExecute = actualTimestamp - startTimestamp;
    }
};

PerformanceGauges performance;