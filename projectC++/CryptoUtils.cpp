#include "CryptoUtils.h"

namespace PassManager {

    const char CryptoUtils::KEY = 0x5A;

    std::string CryptoUtils::encrypt(const std::string& input) {
        std::string result = input;
        for (char& c : result) c ^= KEY;
        return result;
    }

    std::string CryptoUtils::decrypt(const std::string& input) {
        std::string result = input;
        for (char& c : result) c ^= KEY;
        return result;
    }

}