#pragma once
#include "BaseEntity.h"

namespace PassManager {

    class BankPassword : public BaseEntity {
    private:
        std::string bankName;
        std::string cardNumber;
    public:
        explicit BankPassword(const std::string& svc = "",
            const std::string& user = "",
            const std::string& pass = "",
            const std::string& bank = "",
            const std::string& card = "");
        BankPassword(const BankPassword& other);
        ~BankPassword();

        void display() const override;
        std::string getCategory() const override;
        int getStrengthScore() const override;
        void saveToFile(std::ofstream& file) const override;

        std::string getBankName() const { return bankName; }
    };

}