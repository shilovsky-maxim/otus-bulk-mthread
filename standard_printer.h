#pragma once

#include "printer.h"

class StandardOutputPrinter final : public IPrinter
{
public:
    StandardOutputPrinter() = default;
    virtual ~StandardOutputPrinter() override = default;

    void printItem(const IItem& item) const override;
};
