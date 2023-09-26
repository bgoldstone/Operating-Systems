#include <iostream>

const double calculateTime(double clockSpeed, double numberOfInstructions);

int main()
{
    double clockSpeed;
    double numberOfInstructions;
    std::cout << "Welcome to the execution time calculator!" << std::endl;
    std::cout << "Please enter your Clock Speed (MHz): ";
    std::cin >> clockSpeed;
    std::cout << "Please enter the number of instructions you are computing: ";
    std::cin >> numberOfInstructions;
    const double timeInMilliseconds = calculateTime(clockSpeed, numberOfInstructions);
    printf("The time to execute instructions is : %.4f (ms).\n", timeInMilliseconds);

    return 0;
}

/// @brief Calculates the time (in milliseconds) a set number of instructions takes to run given the clock speed.
/// @param clockSpeed Clock Speed of the Processor.
/// @param numberOfInstructions Number of Instructions being computed.
/// @return time (in milliseconds) the number of instructions takes to run.
const double calculateTime(double clockSpeed, double numberOfInstructions)
{
    double time = numberOfInstructions / clockSpeed;
    const double timeInMilliseconds = time / 1000;
    return timeInMilliseconds;
}