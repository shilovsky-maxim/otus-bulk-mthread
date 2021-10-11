#pragma once

#include "item.h"
#include <ostream>

class Command : public IItem
{
public:
    Command(const std::string& name);
    virtual ~Command() override = default;

    void printContent(std::ostream& out) const override;
private:
    std::string m_name;
};