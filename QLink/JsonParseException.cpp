#include "JsonParseException.h"

const char * JsonParseException::what() const noexcept {
    return "Json parse error";
}
