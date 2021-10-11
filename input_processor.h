#pragma once

#include <iostream>
#include "block_factory.h"
#include "block_processor.h"

class IState;
using IStatePtr = std::unique_ptr<IState>;

class IStateFactory;
using IStateFactoryPtr = std::unique_ptr<IStateFactory>;

class InputProcessor final
{
public:
    InputProcessor(IBlockFactory& blockFactory, IBlockProcessor& processor);
    ~InputProcessor();

    void processInput(std::istream& in);

private:
    IStatePtr m_state;
    IStateFactoryPtr m_stateFactory;
};
