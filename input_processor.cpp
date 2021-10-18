#include "input_processor.h"
#include "command.h"


class IState
{
public:
    IState() = default;
    virtual ~IState() = default;

    virtual IStatePtr nextState(IInputProvider& in) = 0;
};
using IStatePtr = std::unique_ptr<IState>;

class IStateFactory
{
public:
    IStateFactory() = default;
    virtual ~IStateFactory() = default;

    virtual IStatePtr makeStartState(IBlockProcessor& processor) const = 0;
    virtual IStatePtr makeDynamicBlockState(IBlockProcessor& processor, IBlockPtr block = {}, unsigned int level = 0u) const = 0;
    virtual IStatePtr makeStaticBlockState(IBlockProcessor& processor, const std::string& line, IBlockPtr block = {}) const = 0;
};

class StartState final : public IState
{
public:
    StartState(const IStateFactory* factory, IBlockProcessor& processor) 
    : m_factory(factory), m_processor(processor)
    {
    }

    IStatePtr nextState(IInputProvider& in) override
    {
        std::string line;
        if (in.getLine(line))
        {
            // Line is read successfully
            // If it's a brace, then start a dynamic block processing
            if(line == "{")
                return m_factory->makeDynamicBlockState(m_processor);
            else 
                return m_factory->makeStaticBlockState(m_processor, line);
        }
        else
        {
            // end of file. As we in the start state, we don't have any active blocks, so we simply return null
            return nullptr;
        }
    }

private:
    const IStateFactory* m_factory{nullptr};
    IBlockProcessor& m_processor;
};

class DynamicBlockState final : public IState
{
public:
    DynamicBlockState(const IStateFactory* factory, IBlockPtr dynBlock, IBlockProcessor& processor, unsigned int level)
    : m_factory(factory), m_block(std::move(dynBlock)), m_processor(processor), m_level(level)
    {
    }

    IStatePtr nextState(IInputProvider& in) override
    {
        std::string line;
        if (in.getLine(line))
        {
            if (line == "}")
            {
                // End of dynamic block. 
                // If the level is 0, then process the block and move to the start state.
                // If the level is not 0, then decrease the level and move to the dynamic block state
                if (m_level > 0)
                {
                    return m_factory->makeDynamicBlockState(m_processor, std::move(m_block), m_level - 1);
                }
                else
                {
                    m_processor.process(*m_block);
                    return m_factory->makeStartState(m_processor);
                }
            }
            else if (line == "{")
            {
                // It's a nested block
                return m_factory->makeDynamicBlockState(m_processor, std::move(m_block),m_level + 1);
            }
            else
            {
                m_block->addItem(std::make_unique<Command>(line));
                return m_factory->makeDynamicBlockState(m_processor, std::move(m_block), m_level);
            }
        }
        else
        {
            // End of file, we don't need to process the block. Quitting
            return nullptr;
        }
    }
private:
    const IStateFactory* m_factory{nullptr};
    IBlockPtr m_block;
    IBlockProcessor& m_processor;
    unsigned int m_level{0u};
};

class StaticBlockState final : public IState
{
public:
    StaticBlockState(const IStateFactory* factory, IBlockPtr block, IBlockProcessor& processor)
    : m_factory(factory), m_block(std::move(block)), m_processor(processor)
    {
    }

    IStatePtr nextState(IInputProvider& in) override
    {
        if (m_block->isFull())
        {
            m_processor.process(*m_block);
            return m_factory->makeStartState(m_processor); 
        }
        std::string line;
        if (in.getLine(line))
        {
            //  We have a line
            if (line=="{")
            {
                m_processor.process(*m_block);
                return m_factory->makeDynamicBlockState(m_processor);
            }
            else
            {
                return m_factory->makeStaticBlockState(m_processor, line, std::move(m_block));
            }
        }
        else
        {
            // It's end of file, we print existing block and quit
            m_processor.process(*m_block);
            return nullptr;
        }
    }

private:
    const IStateFactory* m_factory{nullptr};
    IBlockPtr m_block;
    IBlockProcessor& m_processor;
};

class StateFactory final : public IStateFactory
{
public:
    StateFactory(IBlockFactory& blockFactory)
    : m_blockFactory(blockFactory) 
    {
    }

    IStatePtr makeStartState(IBlockProcessor& processor) const override
    {
        return std::make_unique<StartState>(this, processor);
    }

    IStatePtr makeDynamicBlockState(IBlockProcessor& processor, IBlockPtr block = {}, unsigned int level = 0u) const override
    {
        if (!block)
            block = m_blockFactory.makeDynamicBlock();
        return std::make_unique<DynamicBlockState>(this, std::move(block), processor, level);
    }

    IStatePtr makeStaticBlockState(IBlockProcessor& processor, const std::string& line, IBlockPtr block = {}) const override
    {
        // Create a block
        if (!block)
            block = m_blockFactory.makeStaticBlock();
        block->addItem(std::make_unique<Command>(line));
        return std::make_unique<StaticBlockState>(this, std::move(block), processor);
    }
private:
    IBlockFactory& m_blockFactory;
};

InputProcessor::~InputProcessor() = default;

InputProcessor::InputProcessor(IBlockFactory& blockFactory, IBlockProcessor& processor)
{
    m_stateFactory = std::make_unique<StateFactory>(blockFactory);
    m_state = m_stateFactory->makeStartState(processor);
}

void InputProcessor::processInput(IInputProvider& in)
{
    while (m_state)
    {
        m_state = m_state->nextState(in);
    }
}
