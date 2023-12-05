#include <iostream>
#include <vector>
#include <sstream>
#include <map>

int FIFOPageReplacement(std::vector<int> &inputSequence);
int OptimalPageReplacement(std::vector<int> &inputSequence);
int LeastRecentlyUsedPageReplacement(std::vector<int> &inputSequence);

unsigned int NUMBER_OF_FRAMES;

int main()
{
    std::vector<int> inputSequence;
    std::string inputLine;

    std::cout << "Hello! Welcome to the Memory Page Replacement Algorithm!\n"
              << std::endl;

    // Get number of frames
    std::cout << "Please Enter a number of frames: ";
    std::getline(std::cin, inputLine);
    NUMBER_OF_FRAMES = std::stoi(inputLine);

    // Get input sequence into a vector
    std::cout << "\nPlease Enter a sequence of numbers: ";

    std::getline(std::cin, inputLine);

    std::istringstream iss(inputLine);
    // temp variable to store input
    int inputValue;

    // converts space separated values into individual values
    while (iss >> inputValue)
    {
        inputSequence.push_back(inputValue);
    }

    // Algorithms
    std::cout << "FIFO Page Replacement Algorithm: " << std::endl;
    int fifoPageFaults = FIFOPageReplacement(inputSequence);
    printf("Total Page Faults: %d\n\n", fifoPageFaults);

    std::cout << "Optimal Page Replacement Algorithm: " << std::endl;
    int optimalPageFaults = OptimalPageReplacement(inputSequence);
    printf("Total Page Faults: %d\n\n", optimalPageFaults);

    std::cout << "Least Recently Used Page Replacement Algorithm: " << std::endl;
    int leastRecentlyUsedPageFaults = LeastRecentlyUsedPageReplacement(inputSequence);
    printf("Total Page Faults: %d\n\n", leastRecentlyUsedPageFaults);

    return 0;
}

/// @brief Prints all of the frames in a readable format.
/// @param frames array of frames
/// @param pageFaults number of page faults that have occurred
void printFrames(int frames[], int pageFaults)
{
    std::string output = "";
    for (int i = 0; i < NUMBER_OF_FRAMES; i++)
    {
        if (i < pageFaults)
        {
            output += std::to_string(frames[i]) + " ";
        }
        else
        {
            output += "  ";
        }
    }
    std::cout << output << std::endl;
}

/// @brief Finds the index of a given value in an array.
/// @param arr a pointer to an array of integers
/// @param value the value to search for in the array
/// @return the index of the value in the array, or -1 if the value was not found
int indexOf(const int *arr, int value)
{
    for (int i = 0; i < NUMBER_OF_FRAMES; i++)
    {
        if (arr[i] == value)
        {
            return i;
        }
    }
    return -1;
}

/// @brief Finds the least recently used frame
/// @param frameMap map of frames and values
/// @param allFrames array of frames that are currently in use
/// @return the index of the least recently used frame
int findLeastRecentlyUsed(const std::map<int, int> &frameMap, const int *allFrames)
{
    // Initialize variables to store the least recently used frame and its corresponding value
    int leastRecentlyUsedValue = INT_MAX;
    int leastRecentlyUsedFrame = -1;

    // Iterate over each frame in the frameMap
    for (auto it = frameMap.begin(); it != frameMap.end(); ++it)
    {
        // Get the frame and value from the current iterator
        int frame = it->first;
        int value = it->second;

        // Check if the value is less than the current leastRecentlyUsedValue
        // and if the frame is present in the allFrames array
        if (value < leastRecentlyUsedValue && indexOf(allFrames, frame) != -1)
        {
            // Update the leastRecentlyUsedValue and leastRecentlyUsedFrame
            leastRecentlyUsedValue = value;
            leastRecentlyUsedFrame = frame;
        }
    }

    // Find the index of the least recently used frame in the allFrames array
    return indexOf(allFrames, leastRecentlyUsedFrame);
}

/// @brief FIFO Page Replacement Algorithm
/// @param inputSequence MMU Frame requests
/// @return number of page faults
int FIFOPageReplacement(std::vector<int> &inputSequence)
{
    int pageFaults = 0;
    int nextFrame = 0;
    int allFrames[NUMBER_OF_FRAMES];
    // for each input
    for (int page : inputSequence)
    {
        // if frame not in memory, remove the oldest frame.
        if (indexOf(allFrames, page) == -1)
        {
            allFrames[nextFrame] = page;
            nextFrame = (nextFrame + 1) % NUMBER_OF_FRAMES;
            pageFaults++;
            printf("Page Fault #%d frames: ", pageFaults);
            printFrames(allFrames, pageFaults);
        }
    }
    return pageFaults;
}

/// @brief Optimal Page Replacement Algorithm
/// @param inputSequence MMU Frame requests
/// @return number of page faults
int OptimalPageReplacement(std::vector<int> &inputSequence)
{
    int pageFaults = 0;
    int nextFrame = 0;
    int allFrames[NUMBER_OF_FRAMES];
    // for each input
    for (int page : inputSequence)
    {
        // if frame not in memory, remove the least relevant frame.
        if (indexOf(allFrames, page) == -1)
        {
            // if all frames are not in use
            if (pageFaults < NUMBER_OF_FRAMES)
            {
                allFrames[pageFaults] = page;
            }
            else
            {
                int leastOptimal = INT_MIN;
                // for each frame in use
                for (int j = 0; j < NUMBER_OF_FRAMES; j++)
                {
                    int currentFrame = allFrames[j];
                    // for each input post-current input sequence
                    for (int k = page; k < inputSequence.size(); k++)
                    {
                        // if this frame is the least optimal frame yet, set it to be the leastOptimal.
                        if (currentFrame == inputSequence[k] && k > leastOptimal)
                        {
                            leastOptimal = k;
                            break;
                        }
                    }
                }
                int frameToRemove = 0;
                // if there is a least optimal frame, use that frame.
                if (leastOptimal != INT_MIN)
                {

                    frameToRemove = indexOf(allFrames, inputSequence[leastOptimal]);
                }
                allFrames[frameToRemove] = page;
            }
            pageFaults++;
            printf("Page Fault #%d frames: ", pageFaults);
            printFrames(allFrames, pageFaults);
        }
    }
    return pageFaults;
}
/// @brief Least Recently Used Page Replacement
/// @param inputSequence MMU Frame requests
/// @return number of page faults
int LeastRecentlyUsedPageReplacement(std::vector<int> &inputSequence)
{
    int pageFaults = 0;
    int allFrames[NUMBER_OF_FRAMES];
    std::map<int, int> frameMap;

    // for each input
    for (int i = 0; i < inputSequence.size(); i++)
    {
        // update Least Recently Used Frame
        frameMap[inputSequence[i]] = i;
        // if frame not in memory, remove the least recently used frame.
        if (indexOf(allFrames, inputSequence[i]) == -1)
        {
            int leastRecentlyUsedFrame = pageFaults;

            // if all frames are in use, find the least recently used frame.
            if (pageFaults >= NUMBER_OF_FRAMES)
            {
                leastRecentlyUsedFrame = findLeastRecentlyUsed(frameMap, allFrames);
            }
            allFrames[leastRecentlyUsedFrame] = inputSequence[i];
            pageFaults++;
            printf("Page Fault #%d frames: ", pageFaults);
            printFrames(allFrames, pageFaults);
        }
    }
    return pageFaults;
}