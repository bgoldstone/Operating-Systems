#include <iostream>
int main()
{
    double clockSpeed;
    double numberOfInstructions;
    std::cout << "Welcome to the execution time calculator!" << std::endl;
    std::cout << "Please enter your Clock Speed (MHz): ";
    std::cin >> clockSpeed;
    std::cout << "Please enter the number of instructions you are computing: ";
    std::cin >> numberOfInstructions;
    const double time = numberOfInstructions / clockSpeed / 1000;
    printf("The time to execute instructions is : %.4f (ms).\n", time);

    return 0;
}