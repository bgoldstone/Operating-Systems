#include <iostream>
#include <random>
#include <time.h>

void initArray(int *memory, int size);
void printArray(int *memory, int size);
void setMemory(int *memory, int size);

int main()
{
    // Memory Array.
    const int size = 20;
    int *memoryBytes = new int[size];
    // Pointer to first memory element.

    initArray(memoryBytes, size);
    printArray(memoryBytes, size);
    setMemory(memoryBytes, size);
    printArray(memoryBytes, size);

    delete[] memoryBytes;

    return 0;
}

/// @brief initializes arrays to all zeros.
/// @param memory array to modify.
/// @param size size of array.
void initArray(int *memory, int size)
{
    for (int i = 0; i < size; i++)
    {
        memory[i] = 0;
    }
}

/// @brief Prints array in a readable format.
/// @param memory array to print out.
/// @param size size of the array.
void printArray(int *memory, int size)
{
    std::cout << "[";
    for (int i = 0; i < size; i++)
    {
        std::cout << memory[i] << ", ";
    }
    std::cout << "\b\b]" << std::endl;
}

/// @brief allocates "memory for processes"
/// @param memory memory allocation to set.
/// @param size size of memory.
void setMemory(int *memory, int size)
{
    int *currentByte = memory;
    int *lastByte = &memory[size - 1] + 1;
    // Seed random to current time.
    srand(time(NULL));
    int program = 1;
    while (currentByte < lastByte)
    {
        for (int i = 0; i < rand() % 3 + 1; i++)
        {
            if (currentByte == lastByte)
            {
                break;
            }
            *currentByte = program;
            if (currentByte + 1 == lastByte)
            {
                return;
            }
            else
            {
                currentByte++;
            }
        }
        program++;
    }
}