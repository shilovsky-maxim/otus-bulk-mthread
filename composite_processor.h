#pragma once

#include "block_processor.h"
#include <vector>

class CompositeProcessor final : public IBlockProcessor
{
public:
    CompositeProcessor() = default;
    virtual ~CompositeProcessor() override = default;

    void addProcessor(IBlockProcessorPtr printer);
    void process(const IBlock& block) const override;

private:
    std::vector<IBlockProcessorPtr> m_processors;
};
