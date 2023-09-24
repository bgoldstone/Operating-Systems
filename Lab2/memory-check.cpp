#include <iostream>
#include <random>
#include <time.h>
#include <map>

/// @brief Array structure that contains array and size
struct arrayStruct
{
    int *array;
    int size;
};

void initArray(arrayStruct *memory);
void printArray(arrayStruct *memory);
void setMemory(arrayStruct *memory);
void printMemory(arrayStruct *memory);

int main()
{
    // Memory Array.
    const int size = 20;
    arrayStruct *array = new arrayStruct;
    int *memoryBytes = new int[size];
    array->array = memoryBytes;
    array->size = size;
    // Pointer to first memory element.

    initArray(array);
    printArray(array);
    setMemory(array);
    printMemory(array);

    delete[] memoryBytes;

    return 0;
}

/// @brief initializes arrayStruct to all zeros.
/// @param memory arrayStruct to modify.
void initArray(arrayStruct *memory)
{

    for (int i = 0; i < memory->size; i++)
    {
        memory->array[i] = 0;
    }
}

/// @brief Prints array in a readable format.
/// @param memory arrayStruct to print out.
void printArray(arrayStruct *memory)
{
    std::cout << "[";
    for (int i = 0; i < memory->size; i++)
    {
        std::cout << memory->array[i] << ", ";
    }
    std::cout << "\b\b]" << std::endl;
}

/// @brief allocates "memory for processes"
/// @param memory arrayStruct to allocate.
void setMemory(arrayStruct *memory)
{
    int *currentByte = memory->array;
    int *lastByte = &memory->array[memory->size - 1] + 1;
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

void printMemory(arrayStruct *memory)
{
    std::map<int, int> memoryAllocation;

    // Find how many bytes each array took up.
    for (int i = 0; i < memory->size; i++)
    {
        int programNum = memory->array[i];
        if (memoryAllocation.find(programNum) != memoryAllocation.end())
        {
            memoryAllocation[programNum] = memoryAllocation[programNum] + 1;
        }
        else
        {
            memoryAllocation[programNum] = 1;
        }
    }

    for (auto it = memoryAllocation.begin(); it != memoryAllocation.end(); it++)
    {
        printf("Program %d required %d bytes of memory.\n", it->first, it->second);
        printArray(memory);
    }
}