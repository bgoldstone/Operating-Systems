#pragma once

class SJFProcess
{
public:
    int processNumber;
    int burstTime;
    int remainingBurstTime;
    int arrivalTime;
    int completionTime;
    bool inReadyQueue;
    SJFProcess(int processNumber, int burstTime, int arrivalTime)
    {
        this->processNumber = processNumber;
        this->burstTime = burstTime;
        this->arrivalTime = arrivalTime;
        this->completionTime = 0;
        this->inReadyQueue = false;
    };
};