#include <vector>
#include <iostream>
#include "LCFSProcess.hpp"
#include <stack>

#ifndef CONTEXT_SWITCH_TIME
#define CONTEXT_SWITCH_TIME 0
#endif

void LCFSScheduler(std::vector<LCFSProcess *> &pProcesses);
void printTurnaroundWaitingTime(const std::vector<LCFSProcess *> &pProcesses);

int main()
{
    std::vector<LCFSProcess *> processes;

    // Test Case 1
    processes.push_back(new LCFSProcess(1, 24, 5));
    processes.push_back(new LCFSProcess(2, 3, 2));
    processes.push_back(new LCFSProcess(3, 3, 3));

    // Test Case 2
    // processes.push_back(new LCFSProcess(1, 24, 0));
    // processes.push_back(new LCFSProcess(2, 3, 0));
    // processes.push_back(new LCFSProcess(3, 3, 0));

    // Test Case 3
    // processes.push_back(new LCFSProcess(1, 24, 10));

    if (processes.empty())
    {
        std::cerr << "No processes available for Scheduling!\n";
        exit(EXIT_FAILURE);
    }

    LCFSScheduler(processes);
    printTurnaroundWaitingTime(processes);

    // Deallocates processes from memory.
    for (auto process : processes)
    {
        delete process;
    }

    return 0;
}

/// @brief Schedules processes using First Come First Serve algorithm.
/// @param processes processes to schedule.
void LCFSScheduler(std::vector<LCFSProcess *> &processes)
{
    int time = 0;
    int completedProcesses = 0;
    std::stack<LCFSProcess *> readyQueue;
    LCFSProcess *pPreviousProcess = nullptr;
    bool contextSwitch = false;
    int remainingContextSwitch = CONTEXT_SWITCH_TIME;

    // While not all processes are completed
    while (completedProcesses < processes.size())
    {
        // Check if any new processes need to be inserted
        for (auto currentProcess : processes)
        {
            // if process has arrived, put in ready queue.
            if (currentProcess->arrivalTime == time && !currentProcess->inReadyQueue)
            {
                currentProcess->inReadyQueue = true;
                readyQueue.push(currentProcess);
            }
        }

        // if queue is empty, move on to the next cycle.
        if (readyQueue.empty())
        {
            time++;
            continue;
        }

        // Current Process
        LCFSProcess *pCurrentProcess = readyQueue.top();

        // Context Switch Time
        if (CONTEXT_SWITCH_TIME > 0)
        {
            time++;
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

        // if process still has remaining time.
        if (pCurrentProcess->remainingBursts > 0)
        {
            time++;
            pCurrentProcess->remainingBursts--;
        }

        else
        {
            pCurrentProcess->completionTime = time;
            completedProcesses++;
            pPreviousProcess = pCurrentProcess;
            readyQueue.pop();
            if (!readyQueue.empty())
                readyQueue.top()->remainingBursts;
        }
    }
    pPreviousProcess = nullptr;
    delete pPreviousProcess;
}

/// @brief Prints the turnaround and waiting time for each process and the averages.
/// @param processes scheduled processes.
void printTurnaroundWaitingTime(const std::vector<LCFSProcess *> &processes)
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

    printf("First-Come First-Served\n\tAverage Waiting Time: %.1f\n\tAverage Turnaround Time: %.1f\n", avgWaitingTime, avgTurnaroundTime);
}
