#pragma once

#include "block_processor.h"
#include "thread_pool.h"

class FilePrinter final : public IBlockProcessor
{
public:
    FilePrinter();
    virtual ~FilePrinter() override = default;

    void process(IBlockPtr block);

private:
    ThreadPool<IBlockPtr> m_pool;
};
