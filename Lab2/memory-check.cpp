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

    // keeps track of the program number.
    int programNumber = 1;

    // while not at the end of the memory array.
    while (currentByte < lastByte)
    {
        // for each byte of memory a programNumber allocates.
        for (int i = 0; i < rand() % 3 + 1; i++)
        {
            // if no space in the memory, do not allocate.
            if (currentByte == lastByte)
            {
                break;
            }

            // sets current space to the current program number and updates current byte.
            *currentByte = programNumber;
            currentByte++;
        }
        // increments program number.
        programNumber++;
    }
}

void printMemory(arrayStruct *memory)
{
    // Mapping <programNumber,amountOfMemory>
    std::map<int, int> memoryAllocation;

    // Find how many bytes each array took up.
    for (int i = 0; i < memory->size; i++)
    {
        int programNum = memory->array[i];
        // if programNumber exists in the map
        if (memoryAllocation.find(programNum) != memoryAllocation.end())
        {
            memoryAllocation[programNum] = memoryAllocation[programNum] + 1;
        }
        // otherwise create the key.
        else
        {
            memoryAllocation[programNum] = 1;
        }
    }

    // Print out memory amount for each programNumber
    for (auto it = memoryAllocation.begin(); it != memoryAllocation.end(); it++)
    {
        // Prints the memory allocation for each program number.
        printf("Program %d required %d bytes of memory.\n", it->first, it->second);
        printArray(memory);
    }
}