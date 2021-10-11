#pragma once

#include <iostream>
#include "block.h"

class IBlockProcessor
{
public:
    IBlockProcessor() = default;
    virtual ~IBlockProcessor() = default;

    virtual void process(const IBlock& block) const = 0;
};
using IBlockProcessorPtr = std::unique_ptr<IBlockProcessor>;
