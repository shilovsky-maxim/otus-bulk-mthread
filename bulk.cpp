#include <iostream>
#include <string>
#include <optional>

#include "command.h"

void printUsageString()
{
    std::cout << "Wrong number of parameters." << std::endl;
    std::cout << "Usage: bulk N, where N is the size of command block" << std::endl;
}

std::optional<unsigned int> processParameters(int argc, char *argv[])
{
    if (argc == 2)
    {
        try
        {
            auto blockSize = std::stoi(argv[1]);
            if (blockSize > 0)
                return static_cast<unsigned int>(blockSize);   
        }
        catch(const std::exception& e)
        {
        }
    }
    
    printUsageString();
    return std::nullopt;
}

int main(int argc, char *argv[])
{
    auto blockSize = processParameters(argc, argv);
    if (!blockSize)
        return -1;

    std::cout << "Block size: " << blockSize.value() << std::endl;   
    return 0;
}