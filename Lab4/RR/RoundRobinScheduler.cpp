#include <vector>
#include <iostream>
#include "RRProcess.hpp"

#ifndef CONTEXT_SWITCH_TIME
#define CONTEXT_SWITCH_TIME 0
#endif

#ifndef TIME_QUANTUM
#define TIME_QUANTUM 4
#endif

void RRScheduler(std::vector<RRProcess *> &processes);
void printTurnaroundWaitingTime(std::vector<RRProcess *> &processes);

int main()
{
    std::vector<RRProcess *> processes;
    // Test Case 1
    // processes.push_back(new RRProcess(1, 24, 0));
    // processes.push_back(new RRProcess(2, 3, 0));
    // processes.push_back(new RRProcess(3, 3, 0));

    // Test Case 2
    // processes.push_back(new RRProcess(1, 120, 20));
    // processes.push_back(new RRProcess(2, 7, 5));
    // processes.push_back(new RRProcess(3, 6, 8));
    // processes.push_back(new RRProcess(4, 500, 12));

    // Test Case 3
    // processes.push_back(new RRProcess(3, 3, 7));

    if (processes.size() == 0)
    {
        std::cerr << "No Processes available for Scheduling!\n";
        exit(EXIT_FAILURE);
    }
    RRScheduler(processes);
    printTurnaroundWaitingTime(processes);

    // Deallocate Memory
    for (size_t i = 0; i < processes.size(); i++)
    {
        delete processes.at(i);
    }

    return 0;
}

/// @brief Round Robin Scheduler
/// @param processes Vector of processes
void RRScheduler(std::vector<RRProcess *> &processes)
{
    int time = 0;
    int completedProcesses = 0;
    std::vector<RRProcess *> readyQueue;
    RRProcess *currentProcess;

    while (processes.size() != completedProcesses)
    {
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
        // Gets First Process in ReadyQueue and deletes it
        currentProcess = readyQueue.at(0);
        readyQueue.erase(readyQueue.begin());
        // Goes through Context Switch and Burst Time
        time += CONTEXT_SWITCH_TIME;

        // Adds Time Quantum to timing
        if (currentProcess->remainingBurstTime > TIME_QUANTUM)
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

/// @brief Prints the turnaround and waiting time for each process and the averages.
/// @param processes scheduled processes.
void printTurnaroundWaitingTime(std::vector<RRProcess *> &processes)
{

    double avgTurnaroundTime = 0;
    double avgWaitingTime = 0;

    int currentTurnaroundTime, currentWaitingTime;

    for (size_t i = 0; i < processes.size(); i++)
    {
        RRProcess *currentProcess = processes.at(i);
        currentTurnaroundTime = currentProcess->completionTime - currentProcess->arrivalTime;
        currentWaitingTime = currentTurnaroundTime - currentProcess->burstTime;
        printf("Process %d: Waiting Time: %d Turnaround Time: %d\n",
               currentProcess->processNumber, currentWaitingTime, currentTurnaroundTime);
        avgWaitingTime = avgWaitingTime + currentWaitingTime;
        avgTurnaroundTime = avgTurnaroundTime + currentTurnaroundTime;
    }
    avgTurnaroundTime = avgTurnaroundTime / processes.size();
    avgWaitingTime = avgWaitingTime / processes.size();
    printf("Round Robin\n\tAverage Waiting Time: %.1f\n\tAverage Turnaround Time: %.1f\n", avgWaitingTime, avgTurnaroundTime);
}
