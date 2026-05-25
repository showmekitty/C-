#include "Exception.h"

namespace PassManager {

    PasswordException::PasswordException(const std::string& msg) : message(msg) {}

    const char* PasswordException::what() const noexcept {
        return message.c_str();
    }

}