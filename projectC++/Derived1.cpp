#include "Derived1.h"
#include <cctype>

namespace PassManager {

    SocialPassword::SocialPassword(const std::string& svc, const std::string& user,
        const std::string& pass, const std::string& plat)
        : BaseEntity(svc, user, pass), platform(plat) {
    }

    SocialPassword::SocialPassword(const SocialPassword& other)
        : BaseEntity(other), platform(other.platform) {
    }

    SocialPassword::~SocialPassword() {}

    void SocialPassword::display() const {
        showBasicInfo();
        std::cout << " | Тип: СОЦСЕТЬ | Платформа: " << platform
            << " | Пароль: " << getDecryptedPassword() << std::endl;
    }

    std::string SocialPassword::getCategory() const {
        return "Социальные сети";
    }

    int SocialPassword::getStrengthScore() const {
        std::string pass = getDecryptedPassword();
        int score = 0;
        if (pass.length() >= 8) score++;
        if (pass.length() >= 12) score++;

        bool hasUpper = false, hasLower = false, hasDigit = false, hasSpecial = false;
        for (char c : pass) {
            if (std::isupper((unsigned char)c)) hasUpper = true;
            else if (std::islower((unsigned char)c)) hasLower = true;
            else if (std::isdigit((unsigned char)c)) hasDigit = true;
            else hasSpecial = true;
        }
        if (hasUpper) score++;
        if (hasLower) score++;
        if (hasDigit) score++;
        if (hasSpecial) score++;

        return score;
    }

    void SocialPassword::saveToFile(std::ofstream& file) const {
        file << "Social," << id << "," << service << "," << username << ","
            << getDecryptedPassword() << "," << platform << "\n";
    }

}