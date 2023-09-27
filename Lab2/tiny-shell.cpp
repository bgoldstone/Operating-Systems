/// @author    Benjamin Goldstone (bgoldstone@muhlenberg.edu)
/// @date      9/27/23
/// @brief     This program is an application representing a tiny shell.

#include <iostream>
#define DEFAULT_VALUE "DEFAULT_VALUE"

int main()
{
    std::string command = DEFAULT_VALUE;
    int numOfFiles = 0;
    std::cout << "Welcome to the Tiny Shell! the worlds best shell!" << std::endl;

    while (command != "exit")
    {
        if (command == "addFile")
        {
            numOfFiles++;
        }
        else if (command == "removeFile")
        {
            if (numOfFiles > 0)
            {
                numOfFiles--;
            }
            // Tells user that they cannot remove files since there are zero left.
            else
            {
                std::cout << "Cannot remove file that does not exist!" << std::endl;
            }
        }
        else if (command == "countFile")
        {
            // Tells user the total number of files.
            std::cout << "Number of Files: " << numOfFiles << std::endl;
        }
        else if (command == "help")
        {
            std::cout << "Here are all of the available commands:\n";
            std::cout << "<-------------------------FILE IO------------------------>\n";
            std::cout << "\"addFile\" Adds one file to the system.\n";
            std::cout << "\"removeFile\" Removes one file from the system.\n";
            std::cout << "\"countFile\" Counts the number of files in the system.\n";
            std::cout << "<-------------------------SYSTEM------------------------->\n";
            std::cout << "\"help\" Displays this helpful menu!\n";
            std::cout << "\"exit\" Exit tiny shell.\n";
        }
        else if (command != DEFAULT_VALUE)
        {
            std::cout << "Command: \"" << command << "\" is an invalid Command!";
            std::cout << "\n\nType \"help\" for a list of commands" << std::endl;
        }
        std::cout << ">";
        getline(std::cin, command);
        std::cout << std::endl;
    }
    std::cout << "Thanks for using Tiny Shell!" << std::endl;
    return 0;
}