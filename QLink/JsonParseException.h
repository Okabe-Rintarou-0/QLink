#ifndef JSONPARSEEXCEPTION_H
#define JSONPARSEEXCEPTION_H
#include <exception>
#include <string>

class JsonParseException: public std::exception
{
public:
    JsonParseException() = default;
    ~JsonParseException() = default;
    virtual const char *what(void) const noexcept override;
};

#endif // JSONPARSEEXCEPTION_H
