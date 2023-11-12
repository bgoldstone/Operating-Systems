#include <vector>
#include <iostream>
#include "FCFSProcess.hpp"

#ifndef CONTEXT_SWITCH_TIME
#define CONTEXT_SWITCH_TIME 0;
#endif

void FCFSScheduler(std::vector<FCFSProcess> *processes);
void printTurnaroundWaitingTime(std::vector<FCFSProcess> *processes);

int main()
{
    std::vector<FCFSProcess> *processes = new std::vector<FCFSProcess>;
    // processes->push_back(FCFSProcess(1, 24, 0));
    // processes->push_back(FCFSProcess(2, 3, 0));
    // processes->push_back(FCFSProcess(3, 3, 0));
    FCFSScheduler(processes);
    printTurnaroundWaitingTime(processes);
    delete processes;

    return 0;
}

void FCFSScheduler(std::vector<FCFSProcess> *processes)
{
    int time = 0;
    for (size_t i = 0; i < processes->size(); i++)
    {
        time += CONTEXT_SWITCH_TIME;
        time += processes->at(i).burstTime;
        processes->at(i).completionTime = time;
    }
}

void printTurnaroundWaitingTime(std::vector<FCFSProcess> *processes)
{
    int numberOfProcesses = processes->size();
    if (numberOfProcesses == 0)
        exit(-1);
    int totalTurnaroundTime = 0;
    int totalWaitingTime = 0;
    int currentTurnaroundTime, currentWaitingTime;

    for (size_t i = 0; i < numberOfProcesses; i++)
    {
        FCFSProcess currentProcess = processes->at(i);
        currentTurnaroundTime = currentProcess.completionTime - currentProcess.arrivalTime;
        currentWaitingTime = currentTurnaroundTime - currentProcess.burstTime;
        printf("Process %d: Waiting Time: %d Turnaround Time: %d\n",
               currentProcess.processNumber, currentWaitingTime, currentTurnaroundTime);
        totalWaitingTime += currentWaitingTime;
        totalTurnaroundTime += currentTurnaroundTime;
    }
    printf("First Come First Serve\n\tAverage Waiting Time: %d\n\tAverageTurnaroundTime: %d\n", totalWaitingTime / numberOfProcesses, totalTurnaroundTime / numberOfProcesses);
}
