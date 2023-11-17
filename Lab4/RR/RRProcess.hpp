#pragma once

class RRProcess
{
public:
    int processNumber;
    int burstTime;
    int arrivalTime;
    int completionTime;
    bool inReadyQueue;
    int remainingBurstTime;
    /// @brief Round Robin Process
    /// @param processNumber Process Number
    /// @param burstTime Process Burst Time
    /// @param arrivalTime Process Arrival Time
    RRProcess(int processNumber, int burstTime, int arrivalTime)
    {
        this->processNumber = processNumber;
        this->burstTime = burstTime;
        this->arrivalTime = arrivalTime;
        this->completionTime = 0;
        this->inReadyQueue = false;
        this->remainingBurstTime = burstTime;
    };
    RRProcess(){

    };
};