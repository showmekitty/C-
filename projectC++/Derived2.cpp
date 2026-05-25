#include "Derived2.h"
#include <cctype>

namespace PassManager {

    BankPassword::BankPassword(const std::string& svc, const std::string& user,
        const std::string& pass, const std::string& bank,
        const std::string& card)
        : BaseEntity(svc, user, pass), bankName(bank), cardNumber(card) {
    }

    BankPassword::BankPassword(const BankPassword& other)
        : BaseEntity(other), bankName(other.bankName), cardNumber(other.cardNumber) {
    }

    BankPassword::~BankPassword() {}

    void BankPassword::display() const {
        showBasicInfo();
        std::cout << " | Тип: БАНК | Банк: " << bankName
            << " | Карта: ****" << cardNumber
            << " | Пароль: " << getDecryptedPassword() << std::endl;
    }

    std::string BankPassword::getCategory() const {
        return "Банки";
    }

    int BankPassword::getStrengthScore() const {
        std::string pass = getDecryptedPassword();
        int score = 0;
        if (pass.length() >= 10) score += 2;

        bool hasUpper = false, hasDigit = false, hasSpecial = false;
        for (char c : pass) {
            if (std::isupper((unsigned char)c)) hasUpper = true;
            else if (std::isdigit((unsigned char)c)) hasDigit = true;
            else if (!std::isalnum((unsigned char)c)) hasSpecial = true;
        }
        if (hasUpper) score++;
        if (hasDigit) score++;
        if (hasSpecial) score++;

        return score;
    }

    void BankPassword::saveToFile(std::ofstream& file) const {
        file << "Bank," << id << "," << service << "," << username << ","
            << getDecryptedPassword() << "," << bankName << "," << cardNumber << "\n";
    }

}