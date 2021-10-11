#pragma once

#include <iostream>
#include "item.h"

class IPrinter
{
public:
    IPrinter() = default;
    virtual ~IPrinter() = default;

    virtual void printItem(const IItem& item) const = 0;
};
using IPrinterPtr = std::unique_ptr<IPrinter>;
