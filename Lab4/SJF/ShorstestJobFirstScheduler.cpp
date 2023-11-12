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
    processes->push_back(new SJFProcess(1, 6, 0));
    processes->push_back(new SJFProcess(2, 8, 2));
    processes->push_back(new SJFProcess(3, 7, 4));
    processes->push_back(new SJFProcess(4, 3, 5));

    // processes->push_back(new SJFProcess(1, 6, 0));
    // processes->push_back(new SJFProcess(2, 8, 0));
    // processes->push_back(new SJFProcess(3, 7, 0));
    // processes->push_back(new SJFProcess(4, 3, 0));

    getSizeOfVector(processes);

    if (NUMBER_OF_PROCESSES == 0)
        exit(EXIT_FAILURE);
    SJFScheduler(processes);
    printTurnaroundWaitingTime(processes);

    // Deallocate Memory
    for (size_t i = 0; i < NUMBER_OF_PROCESSES; i++)
    {
        delete processes->at(i);
    }
    delete processes;

    return 0;
}

void SJFScheduler(std::vector<SJFProcess *> *processes)
{
    int time = 0;
    int completedProcesses = 0;
    int previousProcessNumber = -1;
    std::vector<SJFProcess *> readyQueue;
    SJFProcess *currentProcess;

    int smallestBurstTime, SJFProcess, readyQueueIndex;

    // while not all processes are completed
    while (NUMBER_OF_PROCESSES != completedProcesses)
    {
        // keeps track of process index
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

        // Finds SJF
        smallestBurstTime = INT_MAX;
        readyQueueIndex = 0;
        for (auto it = readyQueue.begin(); it != readyQueue.end(); ++it)
        {
            currentProcess = *it;
            // if smallest burst time so far
            if (currentProcess->burstTime < smallestBurstTime)
            {
                smallestBurstTime = currentProcess->burstTime;
                SJFProcess = readyQueueIndex;
            }
            readyQueueIndex++;
        }

        // Gets First Process in ReadyQueue and removes it from ReadyQueue
        currentProcess = readyQueue.at(SJFProcess);
        readyQueue.erase(readyQueue.begin() + SJFProcess);
        // Goes through Context Switch if applicable
        if (previousProcessNumber != currentProcess->processNumber)
        {
            time += CONTEXT_SWITCH_TIME;
            previousProcessNumber = currentProcess->processNumber;
        }
        time++;
        // Changes Remaining Burst Time
        currentProcess->remainingBurstTime--;
        // Sets Completion Time if done and adds one to completed processes.
        if (currentProcess->remainingBurstTime == 0)
        {
            currentProcess->completionTime = time;
            completedProcesses++;
        }
        else
        {
            readyQueue.push_back(currentProcess);
        }
    }
}

void printTurnaroundWaitingTime(std::vector<SJFProcess *> *processes)
{

    int avgTurnaroundTime = 0;
    int avgWaitingTime = 0;

    int currentTurnaroundTime, currentWaitingTime;

    for (size_t i = 0; i < NUMBER_OF_PROCESSES; i++)
    {
        // Gets current process
        SJFProcess *currentProcess = processes->at(i);

        // Calculates Timing
        currentTurnaroundTime = currentProcess->completionTime - currentProcess->arrivalTime;
        currentWaitingTime = currentTurnaroundTime - currentProcess->burstTime;
        // Prints Timing
        printf("Process %d: Waiting Time: %d Turnaround Time: %d\n",
               currentProcess->processNumber, currentWaitingTime, currentTurnaroundTime);

        // Adds to Average Timing
        avgWaitingTime += currentWaitingTime;
        avgTurnaroundTime += currentTurnaroundTime;
    }
    // Prints Average Times
    avgWaitingTime /= NUMBER_OF_PROCESSES;
    avgTurnaroundTime /= NUMBER_OF_PROCESSES;
    printf("First Come First Serve\n\tAverage Waiting Time: %d\n\tAverageTurnaroundTime: %d\n", avgWaitingTime, avgTurnaroundTime);
}

void getSizeOfVector(std::vector<SJFProcess *> *processes)
{
    for (auto i : *processes)
    {
        NUMBER_OF_PROCESSES++;
    }
}
