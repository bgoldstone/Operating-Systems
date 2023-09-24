#include <iostream>
#define DEFAULT_VALUE "DEFAULT_VALUE"

void toLowerString(std::string *str);

int main()
{
    std::string command = DEFAULT_VALUE;
    int numOfFiles = 0;
    std::cout << "Welcome to the tiny terminal! the worlds best terminal!" << std::endl;

    while (command != "exit")
    {
        if (command == "addFile")
        {
            numOfFiles++;
        }
        else if (command == "removeFile")
        {
            if (numOfFiles != 0)
            {
                numOfFiles--;
            }
            else
            {
                std::cout << "Cannot remove file that does not exist!" << std::endl;
            }
        }
        else if (command == "countFile")
        {
            std::cout << "Number of Files: " << numOfFiles << std::endl;
        }
        else if (command != DEFAULT_VALUE)
        {
            std::cout << "Invalid Command!" << std::endl;
        }
        std::cout << ">";
        getline(std::cin, command);
        std::cout << std::endl;
    }
    return 0;
}