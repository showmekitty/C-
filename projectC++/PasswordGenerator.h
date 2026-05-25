#pragma once
#include <string>

namespace PassManager {

    class PasswordGenerator {
    public:
        static std::string generate(int length = 14);
    };

}