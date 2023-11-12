#include <vector>
#include <iostream>
#include "SJFProcess.hpp"

#ifndef CONTEXT_SWITCH_TIME
#define CONTEXT_SWITCH_TIME 0;
#endif

void SJFScheduler(std::vector<SJFProcess *> *processes);
void printTurnaroundWaitingTime(std::vector<SJFProcess *> *processes);
void getSizeOfVector(std::vector<SJFProcess *> *processes);
int NUMBER_OF_PROCESSES = 0;

int main()
{
    std::vector<SJFProcess *> *processes = new std::vector<SJFProcess *>;
    processes->push_back(new SJFProcess(1, 24, 0));
    processes->push_back(new SJFProcess(2, 3, 0));
    processes->push_back(new SJFProcess(3, 3, 0));

    getSizeOfVector(processes);

    if (processes->size() == 0)
        exit(EXIT_FAILURE);
    SJFScheduler(processes);
    printTurnaroundWaitingTime(processes);
    delete processes;

    return 0;
}

void SJFScheduler(std::vector<SJFProcess *> *processes)
{
    int time = 0;
    int completedProcesses = 0;
    std::vector<SJFProcess *> readyQueue;
    SJFProcess *currentProcess;

    while (NUMBER_OF_PROCESSES != completedProcesses)
    {
        int index = 0;
        for (auto it = processes->begin(); it != processes->end(); ++it)
        {
            currentProcess = *it;
            if (currentProcess->arrivalTime <= time && !currentProcess->inReadyQueue)
            {
                currentProcess->inReadyQueue = true;
                readyQueue.push_back(currentProcess);
            }
        }
        // Removes Process
        // Gets First Process in ReadyQueue and deletes it
        currentProcess = readyQueue.at(0);
        // Goes through Context Switch and Burst Time
        time += CONTEXT_SWITCH_TIME;
        time += currentProcess->burstTime;
        // Sets Completion Time
        currentProcess->completionTime = time;
        completedProcesses++;
        readyQueue.erase(readyQueue.begin());
    }
}

void printTurnaroundWaitingTime(std::vector<SJFProcess *> *processes)
{

    int totalTurnaroundTime = 0;
    int totalWaitingTime = 0;

    int currentTurnaroundTime, currentWaitingTime;

    for (size_t i = 0; i < NUMBER_OF_PROCESSES; i++)
    {
        SJFProcess *currentProcess = processes->at(i);
        currentTurnaroundTime = currentProcess->completionTime - currentProcess->arrivalTime;
        currentWaitingTime = currentTurnaroundTime - currentProcess->burstTime;
        printf("Process %d: Waiting Time: %d Turnaround Time: %d\n",
               currentProcess->processNumber, currentWaitingTime, currentTurnaroundTime);
        totalWaitingTime += currentWaitingTime;
        totalTurnaroundTime += currentTurnaroundTime;
    }
    printf("First Come First Serve\n\tAverage Waiting Time: %d\n\tAverageTurnaroundTime: %d\n", totalWaitingTime / NUMBER_OF_PROCESSES, totalTurnaroundTime / NUMBER_OF_PROCESSES);
}

void getSizeOfVector(std::vector<SJFProcess *> *processes)
{
    for (auto i : *processes)
    {
        NUMBER_OF_PROCESSES++;
    }
}
