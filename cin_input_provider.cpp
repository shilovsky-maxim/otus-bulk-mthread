#include "cin_input_provider.h"

#include <iostream>

bool CinInputProvider::getLine(std::string& out)
{
    return std::getline(std::cin, out).good();
}
