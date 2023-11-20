#pragma once

class LRTProcess
{
public:
    int processNumber;
    int burstTime;
    int remainingBurstTime;
    int arrivalTime;
    int completionTime;
    bool inReadyQueue;
    /// @brief Longest Remaining Time Process
    /// @param processNumber Process Number
    /// @param burstTime Process Burst Time
    /// @param arrivalTime Process Arrival Time
    LRTProcess(int processNumber, int burstTime, int arrivalTime)
    {
        this->processNumber = processNumber;
        this->burstTime = burstTime;
        this->arrivalTime = arrivalTime;
        this->completionTime = 0;
        this->inReadyQueue = false;
        this->remainingBurstTime = burstTime;
    };
};