#pragma once

#include "block_processor.h"

class StandardOutputPrinter final : public IBlockProcessor
{
public:
    StandardOutputPrinter() = default;
    virtual ~StandardOutputPrinter() override = default;

    void process(const IBlock& block) const override;
};
