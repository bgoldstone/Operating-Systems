#include <iostream>
#include <unistd.h>
#include <condition_variable>
#include <filesystem>
#include <signal.h>
#include <sys/wait.h>

int main() 
{
    std::cout << "Hello User !!" << std::endl;
    std::cout << "*************************************************" << std::endl;
    std::condition_variable c;
    pid_t child = fork();
    int status;

    std::cout
        << "I am a child process !"
        << " My process id is " << getpid() << std::endl;
    std::cout << "I was created by " << getppid() << std::endl;
    std::cout << "*************************************************" << std::endl;
    std::cout << "I am the Parent Process(" << getppid() << "), waiting for " << getpid() << " to terminate." << std::endl;
    kill(child, SIGTERM);
    std::cout << "Danger Averted!!" << std::endl;

    std::cout << "You are in:\n"<< execl("/usr/bin/pwd","pwd",NULL) << std::endl;
    return 0;
}
