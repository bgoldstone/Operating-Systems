#pragma once

class FCFSProcess
{
public:
    int processNumber;
    int burstTime;
    int arrivalTime;
    int completionTime;
    bool inReadyQueue;
    int remainingBursts;

    /// @brief Process Number
    /// @param processNumber
    /// @param burstTime Process Burst Time
    /// @param arrivalTime Process Arrival Time
    FCFSProcess(int processNumber, int burstTime, int arrivalTime)
    {
        this->processNumber = processNumber;
        this->burstTime = burstTime;
        this->arrivalTime = arrivalTime;
        this->inReadyQueue = false;
        this->remainingBursts = burstTime;
    };
    FCFSProcess(){

    };
};
