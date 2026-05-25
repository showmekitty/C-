#pragma once
#include <iostream>
#include <string>
#include <ctime>
#include <fstream>

namespace PassManager {

    class BaseEntity {
    private:
        static int totalCount;
    protected:
        int id;
        std::string service;
        std::string username;
        std::string encryptedPassword;
        time_t createdAt;
    public:
        explicit BaseEntity(const std::string& svc = "",
            const std::string& user = "",
            const std::string& pass = "");
        BaseEntity(const BaseEntity& other);
        virtual ~BaseEntity();

        virtual void display() const = 0;
        virtual std::string getCategory() const = 0;
        virtual int getStrengthScore() const = 0;

        static int getTotalCount();

        void showBasicInfo() const;

        int getId() const { return id; }
        std::string getService() const { return service; }
        std::string getUsername() const { return username; }
        std::string getDecryptedPassword() const;

        void setService(const std::string& svc);
        void setUsername(const std::string& user);
        void setPassword(const std::string& pass);

        virtual void saveToFile(std::ofstream& file) const = 0;
    };

}