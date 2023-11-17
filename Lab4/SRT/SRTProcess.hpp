#pragma once

class SRTProcess
{
public:
    int processNumber;
    int burstTime;
    int remainingBurstTime;
    int arrivalTime;
    int completionTime;
    bool inReadyQueue;
    /// @brief Shortest Remaining Time Process
    /// @param processNumber Process Number
    /// @param burstTime Process Burst Time
    /// @param arrivalTime Process Arrival Time
    SRTProcess(int processNumber, int burstTime, int arrivalTime)
    {
        this->processNumber = processNumber;
        this->burstTime = burstTime;
        this->arrivalTime = arrivalTime;
        this->completionTime = 0;
        this->inReadyQueue = false;
        this->remainingBurstTime = burstTime;
    };
};