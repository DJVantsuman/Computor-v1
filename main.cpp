#include <iostream>
#include "computor.h"

void printMan()
{

}

int main(int argc, char *argv[])
{
    if (argc == 2)
    {
        std::string str = argv[1];
        if (str == "--help")
            printMan();
        else
            Computor::Instance().start(str);
    }
    else
        std::cout << "EXCEPTION: Wrong number of arguments" << std::endl;
    return 0;
}
