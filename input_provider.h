#pragma once

#include <string>

class IInputProvider
{
public:
    IInputProvider() = default;
    virtual ~IInputProvider() = default;

    virtual bool getLine(std::string& line) = 0;
};