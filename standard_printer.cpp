#include "standard_printer.h"

void StandardOutputPrinter::process(const IBlock& block) const
{
    std::cout << "bulk: ";
    block.printContent(std::cout);
    std::cout << std::endl;
}
