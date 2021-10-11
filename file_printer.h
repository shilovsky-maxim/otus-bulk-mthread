#pragma once

#include "printer.h"

class FilePrinter final : public IPrinter
{
public:
    FilePrinter() = default;
    virtual ~FilePrinter() override = default;

    void printItem(const IItem& item) const;
};
