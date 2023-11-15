#pragma once

class FCFSProcess
{
public:
    int processNumber;
    int burstTime;
    int arrivalTime;
    int completionTime;
    bool inReadyQueue;
    int remainingTime;
    FCFSProcess(int processNumber, int burstTime, int arrivalTime)
    {
        this->processNumber = processNumber;
        this->burstTime = burstTime;
        this->arrivalTime = arrivalTime;
        this->inReadyQueue = false;
        this->remainingTime = burstTime;
    };
    FCFSProcess(){

    };
};
