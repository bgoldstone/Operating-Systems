#include <vector>
#include <iostream>
#include "SJFProcess.hpp"
#include <queue>
#include <algorithm>

#ifndef CONTEXT_SWITCH_TIME
#define CONTEXT_SWITCH_TIME 0
#endif

void SJFScheduler(std::vector<SJFProcess *> &processes);
void printTurnaroundWaitingTime(std::vector<SJFProcess *> &processes);

int main()
{
    std::vector<SJFProcess *> processes;

    // Test case 1
    // processes.push_back(new SJFProcess(1, 6, 0));
    // processes.push_back(new SJFProcess(2, 8, 2));
    // processes.push_back(new SJFProcess(3, 7, 4));
    // processes.push_back(new SJFProcess(4, 3, 5));

    // Test case 2
    // processes.push_back(new SJFProcess(1, 6, 0));
    // processes.push_back(new SJFProcess(2, 8, 0));
    // processes.push_back(new SJFProcess(3, 7, 0));
    // processes.push_back(new SJFProcess(4, 3, 0));

    // Test Case 3
    // processes.push_back(new SJFProcess(1, 3, 0));

    if (processes.size() == 0)
    {
        std::cerr << "No processes available for Scheduling!\n";
        exit(EXIT_FAILURE);
    }
    SJFScheduler(processes);
    printTurnaroundWaitingTime(processes);

    // Deallocate Memory
    SJFProcess *pProcess;
    for (int i = 0; i < processes.size(); i++)
    {
        pProcess = processes.at(i);
        pProcess = nullptr;
        delete pProcess;
    }
    processes.clear();

    return 0;
}

/// @brief Shortest Job First Scheduler
/// @param processes Vector of processes
void SJFScheduler(std::vector<SJFProcess *> &processes)
{
    int time = 0;
    int completedProcesses = 0;
    std::vector<SJFProcess *> readyQueue;
    int smallestBurstTime = INT_MAX;
    int shortestBurstProcess = -1;
    int readyQueueIndex;

    while (completedProcesses < processes.size())
    {
        // Add arriving processes to the ready queue
        for (auto &process : processes)
        {
            if (process->arrivalTime <= time && !process->inReadyQueue)
            {
                readyQueue.push_back(process);
                process->inReadyQueue = true;
            }
        }
        if (!readyQueue.empty())
        {
            SJFProcess *shortestProcess = nullptr;

            readyQueueIndex = 0;
            smallestBurstTime = INT_MAX;
            // Find the process with the smallest burst time
            for (auto process : readyQueue)
            {
                if (process->burstTime < smallestBurstTime)
                {
                    smallestBurstTime = process->burstTime;
                    shortestProcess = process;
                }
            }
            // Remove the shortest process from the ready queue.
            readyQueue.erase(std::remove(readyQueue.begin(), readyQueue.end(), shortestProcess), readyQueue.end());

            // Process the current process
            time += CONTEXT_SWITCH_TIME;
            time += shortestProcess->burstTime;

            shortestProcess->completionTime = time;
            completedProcesses++;
        }
        else
        {
            time++;
        }
    }
}
/// @brief Prints the turnaround and waiting time for each process and the averages
/// @param processes scheduled processes
void printTurnaroundWaitingTime(std::vector<SJFProcess *> &processes)
{

    double avgTurnaroundTime = 0;
    double avgWaitingTime = 0;

    int currentTurnaroundTime, currentWaitingTime;
    SJFProcess *pCurrentProcess;
    for (size_t i = 0; i < processes.size(); i++)
    {
        // Gets current process
        pCurrentProcess = processes.at(i);

        // Calculates Timing
        currentTurnaroundTime = pCurrentProcess->completionTime - pCurrentProcess->arrivalTime;
        currentWaitingTime = currentTurnaroundTime - pCurrentProcess->burstTime;
        // Prints Timing
        printf("Process %d: Waiting Time: %d Turnaround Time: %d\n",
               pCurrentProcess->processNumber, currentWaitingTime, currentTurnaroundTime);

        // Adds to Average Timing
        avgWaitingTime += currentWaitingTime;
        avgTurnaroundTime += currentTurnaroundTime;
    }
    // Prints Average Times
    avgWaitingTime /= processes.size();
    avgTurnaroundTime /= processes.size();
    printf("Shortest Job First\n\tAverage Waiting Time: %.1f\n\tAverage Turnaround Time: %.1f\n", avgWaitingTime, avgTurnaroundTime);
    delete pCurrentProcess;
}
