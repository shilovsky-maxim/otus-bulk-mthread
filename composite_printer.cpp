#include "composite_printer.h"

void CompositePrinter::addPrinter(IPrinterPtr printer)
{
    m_printers.emplace_back(std::move(printer));
}

void CompositePrinter::printItem(const IItem& item) const
{
    for (const auto& printer : m_printers)
    {
        if (printer)
            printer->printItem(item);
    }
}
