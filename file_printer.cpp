#include "file_printer.h"

#include <sstream>
#include <ctime>
#include <fstream>

void FilePrinter::process(const IBlock& block) const
{
    // Get the current timestamp
    std::stringstream fileName;
    fileName << "bulk" << std::time(nullptr) << ".log";
    std::ofstream file;
    file.open(fileName.str());
    block.printContent(file);
    file << std::endl;
    file.close();
}