#include "BadValueExcept.h"

BadValueExcept::BadValueExcept(const std::string& str) : 
    std::runtime_error("Error with value: " + str)
{}