#pragma once
#include <exception>
#include <string>

namespace PassManager {

    class PasswordException : public std::exception {
    private:
        std::string message;
    public:
        explicit PasswordException(const std::string& msg);
        const char* what() const noexcept override;
    };

}