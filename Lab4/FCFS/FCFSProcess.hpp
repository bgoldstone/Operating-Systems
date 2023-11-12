#pragma once

class FCFSProcess
{
public:
    int processNumber;
    int burstTime;
    int arrivalTime;
    int completionTime;
    FCFSProcess(int processNumber, int burstTime, int arrivalTime)
    {
        this->processNumber = processNumber;
        this->burstTime = burstTime;
        this->arrivalTime = arrivalTime;
        this->completionTime = 0;
    };
};