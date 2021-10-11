#pragma once

#include "printer.h"
#include <vector>

class CompositePrinter final : public IPrinter
{
public:
    CompositePrinter() = default;
    virtual ~CompositePrinter() override = default;

    void addPrinter(IPrinterPtr printer);
    void printItem(const IItem& item) const override;

private:
    std::vector<IPrinterPtr> m_printers;
};
