#include <vector>
#include <iostream>
#include "RRProcess.hpp"

#ifndef CONTEXT_SWITCH_TIME
#define CONTEXT_SWITCH_TIME 0;
#endif

#ifndef TIME_QUANTUM
#define TIME_QUANTUM 4;
#endif

void RRScheduler(std::vector<RRProcess *> *processes);
void printTurnaroundWaitingTime(std::vector<RRProcess *> *processes);
void getSizeOfVector(std::vector<RRProcess *> *processes);
int NUMBER_OF_PROCESSES = 0;

int main()
{
    std::vector<RRProcess *> *processes = new std::vector<RRProcess *>;
    processes->push_back(new RRProcess(1, 24, 0));
    processes->push_back(new RRProcess(2, 3, 0));
    processes->push_back(new RRProcess(3, 3, 0));

    getSizeOfVector(processes);

    if (NUMBER_OF_PROCESSES == 0)
    {
        std::cerr << "No Processes available for Scheduling!\n";
        exit(EXIT_FAILURE);
    }
    RRScheduler(processes);
    printTurnaroundWaitingTime(processes);

    // Deallocate Memory
    for (size_t i = 0; i < NUMBER_OF_PROCESSES; i++)
    {
        delete processes->at(i);
    }
    delete processes;

    return 0;
}

void RRScheduler(std::vector<RRProcess *> *processes)
{
    int time = 0;
    int completedProcesses = 0;
    std::vector<RRProcess *> readyQueue;
    RRProcess *currentProcess;

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
        if (readyQueue.empty())
            continue;
        // Gets First Process in ReadyQueue and deletes it
        currentProcess = readyQueue.at(0);
        readyQueue.erase(readyQueue.begin());
        // Goes through Context Switch and Burst Time
        time += CONTEXT_SWITCH_TIME;

        // Adds Time Quantum to timing
        if (currentProcess->remainingBurstTime > 10)
        {
            currentProcess->remainingBurstTime -= TIME_QUANTUM;
            time += TIME_QUANTUM;
        }
        else
        {
            time += currentProcess->remainingBurstTime;
            currentProcess->remainingBurstTime = 0;
        }

        // Sets Completion Time if it is done.
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

void printTurnaroundWaitingTime(std::vector<RRProcess *> *processes)
{

    double avgTurnaroundTime = 0;
    double avgWaitingTime = 0;

    int currentTurnaroundTime, currentWaitingTime;

    for (size_t i = 0; i < NUMBER_OF_PROCESSES; i++)
    {
        RRProcess *currentProcess = processes->at(i);
        currentTurnaroundTime = currentProcess->completionTime - currentProcess->arrivalTime;
        currentWaitingTime = currentTurnaroundTime - currentProcess->burstTime;
        printf("Process %d: Waiting Time: %d Turnaround Time: %d\n",
               currentProcess->processNumber, currentWaitingTime, currentTurnaroundTime);
        avgWaitingTime = avgWaitingTime + currentWaitingTime;
        avgTurnaroundTime = avgTurnaroundTime + currentTurnaroundTime;
    }
    avgTurnaroundTime = avgTurnaroundTime / NUMBER_OF_PROCESSES;
    avgWaitingTime = avgWaitingTime / NUMBER_OF_PROCESSES;
    printf("First Come First Serve\n\tAverage Waiting Time: %.1f\n\tAverageTurnaroundTime: %.1f\n", avgWaitingTime, avgTurnaroundTime);
}

void getSizeOfVector(std::vector<RRProcess *> *processes)
{
    for (auto i : *processes)
    {
        NUMBER_OF_PROCESSES++;
    }
}
