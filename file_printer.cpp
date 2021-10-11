#include "file_printer.h"

#include <sstream>
#include <ctime>
#include <fstream>

void FilePrinter::printItem(const IItem& item) const
{
    // Get the current timestamp
    std::stringstream fileName;
    fileName << "bulk" << std::time(nullptr) << ".log";
    std::fstream file;
    file.open(fileName.str());
    item.printContent(file);
    file << std::endl;
    file.close();
}