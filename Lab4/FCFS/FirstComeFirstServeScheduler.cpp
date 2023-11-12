#include <vector>
#include <iostream>
#include "FCFSProcess.hpp"

#ifndef CONTEXT_SWITCH_TIME
#define CONTEXT_SWITCH_TIME 0;
#endif

void FCFSScheduler(std::vector<FCFSProcess *> *processes);
void printTurnaroundWaitingTime(std::vector<FCFSProcess *> *processes);
void getSizeOfVector(std::vector<FCFSProcess *> *processes);
int NUMBER_OF_PROCESSES = 0;

int main()
{
    std::vector<FCFSProcess *> *processes = new std::vector<FCFSProcess *>;
    processes->push_back(new FCFSProcess(1, 24, 0));
    processes->push_back(new FCFSProcess(2, 3, 0));
    processes->push_back(new FCFSProcess(3, 3, 0));

    getSizeOfVector(processes);

    if (NUMBER_OF_PROCESSES == 0)
        exit(EXIT_FAILURE);
    FCFSScheduler(processes);
    printTurnaroundWaitingTime(processes);
    
    //Deallocate Memory
    for (size_t i = 0; i < NUMBER_OF_PROCESSES; i++)
    {
        delete processes->at(i);
    }
    delete processes;

    return 0;
}

void FCFSScheduler(std::vector<FCFSProcess *> *processes)
{
    int time = 0;
    int completedProcesses = 0;
    std::vector<FCFSProcess *> readyQueue;
    FCFSProcess *currentProcess;

    while (NUMBER_OF_PROCESSES != completedProcesses)
    {
        for (auto it = processes->begin(); it != processes->end(); ++it)
        {
            currentProcess = *it;
            if (currentProcess->arrivalTime <= time && !currentProcess->inReadyQueue)
            {
                currentProcess->inReadyQueue = true;
                readyQueue.push_back(currentProcess);
            }
        }
        // if ready queue is empty don't do anything
        if (readyQueue.size() == 0)
            continue;
        // Gets First Process in ReadyQueue and deletes it
        currentProcess = readyQueue.at(0);
        readyQueue.erase(readyQueue.begin());
        // Goes through Context Switch and Burst Time
        time += CONTEXT_SWITCH_TIME;
        time += currentProcess->burstTime;
        // Sets Completion Time
        currentProcess->completionTime = time;
        // Adds 1 to Completed Processes
        completedProcesses++;
    }
}

void printTurnaroundWaitingTime(std::vector<FCFSProcess *> *processes)
{

    int totalTurnaroundTime = 0;
    int totalWaitingTime = 0;

    int currentTurnaroundTime, currentWaitingTime;

    for (size_t i = 0; i < NUMBER_OF_PROCESSES; i++)
    {
        FCFSProcess *currentProcess = processes->at(i);
        currentTurnaroundTime = currentProcess->completionTime - currentProcess->arrivalTime;
        currentWaitingTime = currentTurnaroundTime - currentProcess->burstTime;
        printf("Process %d: Waiting Time: %d Turnaround Time: %d\n",
               currentProcess->processNumber, currentWaitingTime, currentTurnaroundTime);
        totalWaitingTime += currentWaitingTime;
        totalTurnaroundTime += currentTurnaroundTime;
    }
    printf("First Come First Serve\n\tAverage Waiting Time: %d\n\tAverageTurnaroundTime: %d\n", totalWaitingTime / NUMBER_OF_PROCESSES, totalTurnaroundTime / NUMBER_OF_PROCESSES);
}

void getSizeOfVector(std::vector<FCFSProcess *> *processes)
{
    for (auto i : *processes)
    {
        NUMBER_OF_PROCESSES++;
    }
}
