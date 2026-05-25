#pragma once
#include "BaseEntity.h"

namespace PassManager {

    class SocialPassword : public BaseEntity {
    private:
        std::string platform;
    public:
        explicit SocialPassword(const std::string& svc = "",
            const std::string& user = "",
            const std::string& pass = "",
            const std::string& plat = "Другое");
        SocialPassword(const SocialPassword& other);
        ~SocialPassword();

        void display() const override;
        std::string getCategory() const override;
        int getStrengthScore() const override;
        void saveToFile(std::ofstream& file) const override;

        std::string getPlatform() const { return platform; }
    };

}