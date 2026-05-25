#include "BaseEntity.h"
#include "CryptoUtils.h"

namespace PassManager {

    int BaseEntity::totalCount = 0;

    BaseEntity::BaseEntity(const std::string& svc, const std::string& user, const std::string& pass)
        : service(svc), username(user) {
        id = ++totalCount;
        createdAt = std::time(nullptr);
        encryptedPassword = CryptoUtils::encrypt(pass);
    }

    BaseEntity::BaseEntity(const BaseEntity& other)
        : id(other.id), service(other.service), username(other.username),
        encryptedPassword(other.encryptedPassword), createdAt(other.createdAt) {
    }

    BaseEntity::~BaseEntity() {}

    int BaseEntity::getTotalCount() {
        return totalCount;
    }

    void BaseEntity::showBasicInfo() const {
        std::cout << "ID: " << id << " | Сервис: " << service
            << " | Логин: " << username;
    }

    std::string BaseEntity::getDecryptedPassword() const {
        return CryptoUtils::decrypt(encryptedPassword);
    }

    void BaseEntity::setService(const std::string& svc) {
        this->service = svc;
    }

    void BaseEntity::setUsername(const std::string& user) {
        this->username = user;
    }

    void BaseEntity::setPassword(const std::string& pass) {
        this->encryptedPassword = CryptoUtils::encrypt(pass);
    }

}