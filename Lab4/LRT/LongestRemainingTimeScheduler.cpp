#include <vector>
#include <iostream>
#include "LRTProcess.hpp"

#ifndef CONTEXT_SWITCH_TIME
#define CONTEXT_SWITCH_TIME 0;
#endif

void LRTScheduler(std::vector<LRTProcess *> &processes);
void printTurnaroundWaitingTime(std::vector<LRTProcess *> &processes);
void getSizeOfVector(std::vector<LRTProcess *> &processes);

int main()
{
    std::vector<LRTProcess *> processes;

    // Test Case 1
    // processes.push_back(new LRTProcess(1, 8, 0));
    // processes.push_back(new LRTProcess(2, 4, 1));
    // processes.push_back(new LRTProcess(3, 9, 2));
    // processes.push_back(new LRTProcess(4, 5, 3));

    // Test Case 2
    processes.push_back(new LRTProcess(1, 6, 0));
    processes.push_back(new LRTProcess(2, 8, 0));
    processes.push_back(new LRTProcess(3, 7, 0));
    processes.push_back(new LRTProcess(4, 3, 0));

    // Test Case 3
    // processes.push_back(new LRTProcess(4, 5, 3));

    if (processes.size() == 0)
    {
        std::cerr << "No Processes available for Scheduling!\n";
        exit(EXIT_FAILURE);
    }
    LRTScheduler(processes);
    printTurnaroundWaitingTime(processes);

    // Deallocate Memory
    for (size_t i = 0; i < processes.size(); i++)
    {
        delete processes.at(i);
    }

    return 0;
}

/// @brief Shortest Remaining Time Scheduler
/// @param processes Vector of SRT Processes
void LRTScheduler(std::vector<LRTProcess *> &processes)
{
    int time = 0;
    int completedProcesses = 0;
    int previousProcessNumber = -1;
    std::vector<LRTProcess *> readyQueue;
    LRTProcess *currentProcess;

    int longestRemainingBurstTime, LRTProcess, readyQueueIndex;

    // while not all processes are completed
    while (processes.size() != completedProcesses)
    {
        // keeps track of process index
        for (auto it = processes.begin(); it != processes.end(); ++it)
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
        {
            time++;
            continue;
        }

        // Finds LRT
        longestRemainingBurstTime = INT_MIN;
        readyQueueIndex = 0;
        for (auto it = readyQueue.begin(); it != readyQueue.end(); ++it)
        {
            currentProcess = *it;
            // if smallest burst time so far
            if (currentProcess->remainingBurstTime > longestRemainingBurstTime)
            {
                longestRemainingBurstTime = currentProcess->burstTime;
                LRTProcess = readyQueueIndex;
            }
            readyQueueIndex++;
        }

        // Gets First Process in ReadyQueue and removes it from ReadyQueue
        currentProcess = readyQueue.at(LRTProcess);
        readyQueue.erase(readyQueue.begin() + LRTProcess);
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

/// @brief Prints Turnaround and Waiting Times
/// @param processes scheduled processes
void printTurnaroundWaitingTime(std::vector<LRTProcess *> &processes)
{

    double avgTurnaroundTime = 0;
    double avgWaitingTime = 0;

    int currentTurnaroundTime, currentWaitingTime;

    for (size_t i = 0; i < processes.size(); i++)
    {
        // Gets current process
        LRTProcess *currentProcess = processes.at(i);

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
    avgWaitingTime /= processes.size();
    avgTurnaroundTime /= processes.size();
    printf("Longest Remaining Time\n\tAverage Waiting Time: %.1f\n\tAverage Turnaround Time: %.1f\n", avgWaitingTime, avgTurnaroundTime);
}
