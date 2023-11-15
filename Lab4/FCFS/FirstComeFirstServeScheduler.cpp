#include <vector>
#include <iostream>
#include "FCFSProcess.hpp"
#include <queue>

#ifndef CONTEXT_SWITCH_TIME
#define CONTEXT_SWITCH_TIME 0
#endif

void FCFSScheduler(std::vector<FCFSProcess *> &processes);
void printTurnaroundWaitingTime(const std::vector<FCFSProcess *> &processes);

int main()
{
    std::vector<FCFSProcess *> processes;
    processes.push_back(new FCFSProcess(1, 24, 5));
    processes.push_back(new FCFSProcess(2, 3, 2));
    processes.push_back(new FCFSProcess(3, 3, 3));

    if (processes.empty())
    {
        std::cerr << "No Processes available for Scheduling!\n";
        exit(EXIT_FAILURE);
    }

    FCFSScheduler(processes);
    printTurnaroundWaitingTime(processes);

    // Deallocate Memory
    for (auto process : processes)
    {
        delete process;
    }

    return 0;
}

void FCFSScheduler(std::vector<FCFSProcess *> &processes)
{
    int time = 0;
    int completedProcesses = 0;
    std::queue<FCFSProcess *> readyQueue;
    FCFSProcess *pPreviousProcess = nullptr;
    bool contextSwitch = false;
    int remainingContextSwitch = CONTEXT_SWITCH_TIME;

    while (completedProcesses < processes.size())
    {
        for (auto currentProcess : processes)
        {
            // if process has arrived, put in ready queue.
            if (currentProcess->arrivalTime == time && !currentProcess->inReadyQueue)
            {
                currentProcess->inReadyQueue = true;
                readyQueue.push(currentProcess);
            }
        }

        if (readyQueue.empty())
        {
            time++;
            continue;
        }

        FCFSProcess *pCurrentProcess = readyQueue.front();

        if (CONTEXT_SWITCH_TIME > 0)
        {
            if (pCurrentProcess != pPreviousProcess && !contextSwitch)
            {
                contextSwitch = true;
                remainingContextSwitch--;
            }

            if (contextSwitch && remainingContextSwitch == 0)
            {
                contextSwitch = false;
                remainingContextSwitch = CONTEXT_SWITCH_TIME;
            }
        }

        if (pCurrentProcess->remainingTime > 0)
        {
            time++;
            pCurrentProcess->remainingTime--;
        }
        else
        {
            pCurrentProcess->completionTime = time++;
            completedProcesses++;
            pPreviousProcess = pCurrentProcess;
            readyQueue.pop();
            if (!readyQueue.empty())
                readyQueue.front()->remainingTime--;
        }
    }
}

void printTurnaroundWaitingTime(const std::vector<FCFSProcess *> &processes)
{
    double avgTurnaroundTime = 0;
    double avgWaitingTime = 0;

    for (auto currentProcess : processes)
    {
        int currentTurnaroundTime = currentProcess->completionTime - currentProcess->arrivalTime;
        int currentWaitingTime = currentTurnaroundTime - currentProcess->burstTime;

        printf("Process %d: Waiting Time: %d Turnaround Time: %d\n",
               currentProcess->processNumber, currentWaitingTime, currentTurnaroundTime);

        avgWaitingTime += currentWaitingTime;
        avgTurnaroundTime += currentTurnaroundTime;
    }

    avgTurnaroundTime /= processes.size();
    avgWaitingTime /= processes.size();

    printf("First Come First Serve\n\tAverage Waiting Time: %.1f\n\tAverage Turnaround Time: %.1f\n", avgWaitingTime, avgTurnaroundTime);
}
