#include <iostream>
#include <vector>
#include <sstream>
#include <map>

void printFrames(int frames[]);
int indexOf(int arr[], int value);
int findLeastRecentlyUsed(std::map<int, int> &frameMap, int frames[]);
int FIFOPageReplacement(std::vector<int> &inputSequence);
int OptimalPageReplacement(std::vector<int> &inputSequence);
int LeastRecentlyUsedPageReplacement(std::vector<int> &inputSequence);

int NUMBER_OF_FRAMES;

int main()
{
    std::vector<int> inputSequence;
    std::string inputLine;

    std::cout << "Hello! Welcome to the Memory Page Replacement Algorithm!!\n"
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

    for (int i = 0; i < NUMBER_OF_FRAMES; i++)
    {
        if (i < pageFaults)
        {
            std::cout << frames[i] << " ";
            continue;
        }
        std::cout << "  ";
    }
    std::cout << std::endl;
}

/// @brief Finds the index of a value in an array
/// @param arr array to search
/// @param value value to search for
/// @return index of value in array, -1 if not found
int indexOf(int arr[], int value)
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
int findLeastRecentlyUsed(std::map<int, int> &frameMap, int allFrames[])
{
    int leastRecentlyUsedFrame;
    int leastRecentlyUsedValue = INT_MAX;
    for (const auto &[frame, value] : frameMap)
    {
        // if value is less than least recently used value and frame is in use, set it as least recently used.
        if (value < leastRecentlyUsedValue && indexOf(allFrames, frame) != -1)
        {
            leastRecentlyUsedValue = value;
            leastRecentlyUsedFrame = frame;
        }
    }
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
    for (int i = 0; i < inputSequence.size(); i++)
    {
        // if frame not in memory, remove the oldest frame.
        if (indexOf(allFrames, inputSequence[i]) == -1)
        {
            allFrames[nextFrame] = inputSequence[i];
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
    for (int i = 0; i < inputSequence.size(); i++)
    {
        // if frame not in memory, remove the least relevant frame.
        if (indexOf(allFrames, inputSequence[i]) == -1)
        {
            // if all frames are not in use
            if (pageFaults < NUMBER_OF_FRAMES)
            {
                allFrames[pageFaults] = inputSequence[i];
            }
            else
            {
                int leastOptimal = INT_MIN;
                // for each frame in use
                for (int j = 0; j < NUMBER_OF_FRAMES; j++)
                {
                    int currentFrame = allFrames[j];
                    // for each input post-current input sequence
                    for (int k = i; k < inputSequence.size(); k++)
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
                allFrames[frameToRemove] = inputSequence[i];
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
    int nextFrame = 0;
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