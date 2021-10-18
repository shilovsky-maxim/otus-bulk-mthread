#include <iostream>
#include <string>
#include <optional>

#include "input_processor.h"
#include "default_block_factory.h"
#include "standard_printer.h"
#include "file_printer.h"
#include "composite_processor.h"
#include "cin_input_provider.h"

void printUsageString()
{
    std::cout << "Wrong number of parameters." << std::endl;
    std::cout << "Usage: bulk N, where N is the size of command block" << std::endl;
}

std::optional<size_t> processParameters(int argc, char *argv[])
{
    if (argc == 2)
    {
        try
        {
            auto blockSize = std::stoi(argv[1]);
            if (blockSize > 0)
                return static_cast<size_t>(blockSize);   
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

    DefaultBlockFactory factory(blockSize.value());
    CompositeProcessor printer;
    printer.addProcessor(std::make_unique<FilePrinter>());
    printer.addProcessor(std::make_unique<StandardOutputPrinter>());

    CinInputProvider in;
    InputProcessor processor(factory, printer);
    processor.processInput(in);
       
    return 0;
}