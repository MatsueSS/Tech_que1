#include "FileException.h"

FileException::FileException(const std::string& filename) : 
    std::runtime_error("Cannot be opened file: " + filename)
{}