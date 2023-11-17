#pragma once

class SJFProcess
{
public:
    int processNumber;
    int burstTime;
    int remainingBursts;
    int arrivalTime;
    int completionTime;
    bool inReadyQueue;
    /// @brief Shortest Job First Process
    /// @param processNumber Process Number
    /// @param burstTime Process Burst Time
    /// @param arrivalTime Process Arrival Time
    SJFProcess(int processNumber, int burstTime, int arrivalTime)
    {
        this->processNumber = processNumber;
        this->burstTime = burstTime;
        this->arrivalTime = arrivalTime;
        this->completionTime = 0;
        this->inReadyQueue = false;
        this->remainingBursts = burstTime;
    };
};
