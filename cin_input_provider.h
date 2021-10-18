#pragma once

#include "input_provider.h"

class CinInputProvider final : public IInputProvider
{
public:
    CinInputProvider() = default;
    virtual ~CinInputProvider() override = default;

    bool getLine(std::string& out) override;
};

