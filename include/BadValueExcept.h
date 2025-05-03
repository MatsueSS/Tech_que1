#ifndef _BAD_VALUE_ERROR_H_
#define _BAD_VALUE_ERROR_H_

#include <stdexcept>
#include <string>

class BadValueExcept : public std::runtime_error{
public:
    explicit BadValueExcept(const std::string&);
};

#endif //_BAD_VALUE_ERROR_H_