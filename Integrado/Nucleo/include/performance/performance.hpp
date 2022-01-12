#pragma once

struct PerformanceGauges {
    unsigned long startTimestamp;
    int timeToExecute;
    int numberOfTaks;
    long freeMemory;
    long stackWaterMark;

    void measure(unsigned long actualTimestamp, int tasks, long heap, long stackWM) {
        timeToExecute = actualTimestamp - startTimestamp;
        numberOfTaks = tasks;
        freeMemory = heap;
        stackWaterMark = stackWM;
    }
};

PerformanceGauges performance;