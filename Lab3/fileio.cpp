#include <iostream>
#include <string>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>

extern int errno;

int main()
{

    // Creates/Replaces file and opens in write mode.
    int fileDescriptor = open("sample.txt", O_CREAT | O_WRONLY | O_TRUNC);
    std::cout << "File Descriptor: " << fileDescriptor << std::endl;
    if (fileDescriptor == -1)
    {
        std::cerr << "Error Opening File: " << errno << std::endl;
        exit(errno);
    }

    std::string str = "Hello System Calls!";
    int writeToFile = write(fileDescriptor, str.c_str(), str.size());
    if (writeToFile == -1)
    {
        std::cerr << "Error Writing to File: " << errno << std::endl;
    }
    close(fileDescriptor);
    return 0;
}
