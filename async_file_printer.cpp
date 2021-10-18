#include "async_file_printer.h"

#include <sstream>
#include <ctime>
#include <fstream>
#include <atomic>

static void printBlock(IBlockPtr block, size_t threadIndex)
{
    static std::atomic<unsigned int> counter = 0u;
    // Get the current timestamp
    std::stringstream fileName;
    ++counter;
    fileName << "bulk" << std::time(nullptr) << "_file_" << (threadIndex + 1) << "_" << counter << ".log";
    std::ofstream file;
    file.open(fileName.str());
    block->printContent(file);
    file << std::endl;
    file.close();
}

FilePrinter::FilePrinter()
: m_pool(2, printBlock) 
{
}

void FilePrinter::process(IBlockPtr block)
{
    m_pool.addData(block);
}