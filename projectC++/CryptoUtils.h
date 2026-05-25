#pragma once
#include <string>

namespace PassManager {

    class CryptoUtils {
    private:
        static const char KEY;
    public:
        static std::string encrypt(const std::string& input);
        static std::string decrypt(const std::string& input);
    };

}