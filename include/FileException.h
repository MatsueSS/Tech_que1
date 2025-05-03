#ifndef _FILE_EXCEPTION_H_
#define _FILE_EXCEPTION_H_

#include <stdexcept>
#include <string>

class FileException : public std::runtime_error{
public:
    explicit FileException(const std::string&);
};

#endif //_FILE_EXCEPTION_H_