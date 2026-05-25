#include "PasswordGenerator.h"
#include <random>
#include <ctime>

namespace PassManager {

    std::string PasswordGenerator::generate(int length) {
        const std::string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz"
            "0123456789"
            "!@#$%^&*";

        std::mt19937 rng((unsigned int)std::time(nullptr));
        std::uniform_int_distribution<int> dist(0, (int)chars.length() - 1);

        std::string password;
        for (int i = 0; i < length; i++) {
            password += chars[dist(rng)];
        }
        return password;
    }

}