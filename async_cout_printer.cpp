#include "async_cout_printer.h"

static void printBlock(IBlockPtr block, size_t)
{
    if (!block)
        return;
    std::cout << "bulk: ";
    block->printContent(std::cout);
    std::cout << std::endl;
}

AsyncCoutPrinter::AsyncCoutPrinter()
: m_pool(1, printBlock)
{
}

void AsyncCoutPrinter::process(IBlockPtr block)
{
    m_pool.addData(block);
}
