#pragma once

#include "block_processor.h"
#include "thread_pool.h"

class AsyncCoutPrinter final : public IBlockProcessor
{
public:
    AsyncCoutPrinter();
    virtual ~AsyncCoutPrinter() override = default;

    void process(IBlockPtr block) override;

private:
    ThreadPool<IBlockPtr> m_pool;
};
