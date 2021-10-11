#include "standard_printer.h"

void StandardOutputPrinter::printItem(const IItem& item) const
{
    item.printContent(std::cout);
    std::cout << std::endl;
}
