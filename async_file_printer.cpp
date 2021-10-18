#include "async_file_printer.h"

#include <sstream>
#include <ctime>
#include <fstream>
#include <atomic>

static std::string formTimestamp()
{
    std::stringstream timestamp;
    timestamp << "bulk" << std::time(nullptr);
    return timestamp.str();
}

static void printCommand(const std::string& timestamp, IItemPtr item, size_t threadIndex)
{
    if (!item)
        return;
    // Get the current timestamp
    std::stringstream fileName;
    fileName << timestamp << "_file_" << (threadIndex + 1) << ".log";
    std::ofstream file;
    file.open(fileName.str(), std::ofstream::app);
    item->printContent(file);
    file << std::endl;
    file.close();
}

using namespace std::placeholders;
FilePrinter::FilePrinter()
: m_name(formTimestamp()), m_pool(2, std::bind(printCommand, m_name, _1, _2))
{
}

void FilePrinter::process(IBlockPtr block)
{
    for (auto item : block->getItems())
        m_pool.addData(item);
}