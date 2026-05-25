#include <iostream>
#include <memory>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <limits>
#include <windows.h>

#include "Exception.h"
#include "BaseEntity.h"
#include "Derived1.h"
#include "Derived2.h"
#include "Stack.h"
#include "Repository.h"
#include "PasswordGenerator.h"

using namespace PassManager;
using namespace std;

Repository<BaseEntity> repo;
Stack<shared_ptr<BaseEntity>> undoStack;

void loadFromFile();
void saveToFile();
void addPassword();
void viewAll();
void editPassword();
void deletePassword();
void searchPassword();
void sortPasswords();
void showStats();
void generatePassword();

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    cout << "\n========================================\n";
    cout << "       МЕНЕДЖЕР ПАРОЛЕЙ v1.0\n";
    cout << "========================================\n";
    cout << "Все пароли шифруются автоматически\n\n";

    try {
        loadFromFile();

        int choice;
        do {
            cout << "\n========================================\n";
            cout << "  1. Добавить пароль\n";
            cout << "  2. Показать все пароли\n";
            cout << "  3. Редактировать пароль\n";
            cout << "  4. Удалить пароль\n";
            cout << "  5. Поиск по сервису\n";
            cout << "  6. Сортировка по названию\n";
            cout << "  7. Статистика\n";
            cout << "  8. Сгенерировать пароль\n";
            cout << "  0. Сохранить и выйти\n";
            cout << "========================================\n";
            cout << "Выберите пункт: ";
            cin >> choice;

            switch (choice) {
            case 1: addPassword(); break;
            case 2: viewAll(); break;
            case 3: editPassword(); break;
            case 4: deletePassword(); break;
            case 5: searchPassword(); break;
            case 6: sortPasswords(); break;
            case 7: showStats(); break;
            case 8: generatePassword(); break;
            case 0:
                saveToFile();
                cout << "Данные сохранены. До свидания!\n";
                break;
            default:
                cout << "Неверный выбор\n";
            }
        } while (choice != 0);

    }
    catch (const PasswordException& e) {
        cerr << "Ошибка: " << e.what() << endl;
    }
    catch (const exception& e) {
        cerr << "Системная ошибка: " << e.what() << endl;
    }

    return 0;
}

void addPassword() {
    int type;
    cout << "\n--- Добавление пароля ---\n";
    cout << "1. Социальная сеть\n";
    cout << "2. Банк/Карта\n";
    cout << "Тип: ";
    cin >> type;
    cin.ignore(32767, '\n');

    string service, username, password, extra1, extra2;

    cout << "Название сервиса: ";
    getline(cin, service);

    cout << "Логин: ";
    getline(cin, username);

    cout << "Пароль (или 'gen' для генерации): ";
    getline(cin, password);

    if (password == "gen" || password == "GEN") {
        password = PasswordGenerator::generate(14);
        cout << "Сгенерирован пароль: " << password << endl;
    }

    shared_ptr<BaseEntity> entity;

    if (type == 1) {
        cout << "Платформа (VK/Telegram/Instagram): ";
        getline(cin, extra1);
        entity = make_shared<SocialPassword>(service, username, password, extra1);
    }
    else {
        cout << "Название банка: ";
        getline(cin, extra1);
        cout << "Последние 4 цифры карты: ";
        getline(cin, extra2);
        entity = make_shared<BankPassword>(service, username, password, extra1, extra2);
    }

    repo.add(entity);
    undoStack.push(entity);
    cout << "\nПароль добавлен! ID: " << entity->getId() << endl;
}

void viewAll() {
    if (repo.size() == 0) {
        cout << "\nНет сохранённых паролей\n";
        return;
    }

    cout << "\n=== ВСЕ ПАРОЛИ ===\n";
    cout << "------------------------------------------------\n";

    for (auto& item : repo) {
        item->display();
    }

    cout << "------------------------------------------------\n";
    cout << "Всего: " << repo.size() << " паролей\n";
}

void editPassword() {
    if (repo.size() == 0) {
        cout << "Нет паролей для редактирования\n";
        return;
    }

    int id;
    cout << "Введите ID пароля: ";
    cin >> id;
    cin.ignore(32767, '\n');

    auto entity = repo.findById(id);
    if (!entity) {
        cout << "Пароль не найден\n";
        return;
    }

    cout << "\nРедактирование:\n";
    entity->display();

    string newService, newUsername, newPassword;
    cout << "\nНовое название (Enter = оставить): ";
    getline(cin, newService);
    if (!newService.empty()) entity->setService(newService);

    cout << "Новый логин (Enter = оставить): ";
    getline(cin, newUsername);
    if (!newUsername.empty()) entity->setUsername(newUsername);

    cout << "Новый пароль (Enter = оставить, 'gen'): ";
    getline(cin, newPassword);
    if (newPassword == "gen") newPassword = PasswordGenerator::generate(14);
    if (!newPassword.empty()) entity->setPassword(newPassword);

    cout << "Пароль обновлён!\n";
}

void deletePassword() {
    if (repo.size() == 0) {
        cout << "Нет паролей для удаления\n";
        return;
    }

    int id;
    cout << "Введите ID пароля: ";
    cin >> id;

    auto entity = repo.findById(id);
    if (!entity) {
        cout << "Пароль не найден\n";
        return;
    }

    cout << "\nУдаление:\n";
    entity->display();

    char confirm;
    cout << "\nВы уверены? (y/n): ";
    cin >> confirm;

    if (confirm == 'y' || confirm == 'Y') {
        repo.remove(id);
        cout << "Пароль удалён\n";
    }
    else {
        cout << "Отменено\n";
    }
}

void searchPassword() {
    if (repo.size() == 0) {
        cout << "Нет паролей для поиска\n";
        return;
    }

    cin.ignore(32767, '\n');
    string query;
    cout << "Введите название сервиса: ";
    getline(cin, query);

    auto results = repo.findByService(query);

    if (results.empty()) {
        cout << "Ничего не найдено\n";
        return;
    }

    cout << "\n=== РЕЗУЛЬТАТЫ ===\n";
    for (auto& item : results) {
        item->display();
    }
}

void sortPasswords() {
    if (repo.size() == 0) {
        cout << "Нет паролей для сортировки\n";
        return;
    }

    vector<shared_ptr<BaseEntity>> sorted;
    for (auto& item : repo) {
        sorted.push_back(item);
    }

    // ЛЯМБДА ДЛЯ СОРТИРОВКИ
    sort(sorted.begin(), sorted.end(), [](shared_ptr<BaseEntity> a, shared_ptr<BaseEntity> b) {
        return a->getService() < b->getService();
        });

    cout << "\n=== СОРТИРОВКА ПО НАЗВАНИЮ ===\n";
    for (auto& item : sorted) {
        item->display();
    }
}

void showStats() {
    if (repo.size() == 0) {
        cout << "Нет данных для статистики\n";
        return;
    }

    int socialCount = 0, bankCount = 0;
    int weak = 0, medium = 0, strong = 0;

    for (auto& item : repo) {
        int score = item->getStrengthScore();
        if (score <= 3) weak++;
        else if (score <= 5) medium++;
        else strong++;

        if (item->getCategory() == "Социальные сети") socialCount++;
        else if (item->getCategory() == "Банки") bankCount++;
    }

    cout << "\n=== СТАТИСТИКА ===\n";
    cout << "Всего паролей: " << repo.size() << "\n";
    cout << "Социальные сети: " << socialCount << "\n";
    cout << "Банки: " << bankCount << "\n";
    cout << "\nСложность паролей:\n";
    cout << "  Слабые:   " << weak << "\n";
    cout << "  Средние:  " << medium << "\n";
    cout << "  Сильные:  " << strong << "\n";
}

void generatePassword() {
    int length;
    cout << "Длина пароля (8-24, по умолчанию 14): ";
    cin >> length;

    if (length < 8) length = 8;
    if (length > 24) length = 24;

    string newPass = PasswordGenerator::generate(length);
    cout << "\nСгенерированный пароль: " << newPass << "\n";

    int score = 0;
    if (newPass.length() >= 12) score += 2;
    bool hasUpper = false, hasDigit = false, hasSpecial = false;
    for (char c : newPass) {
        if (isupper(c)) hasUpper = true;
        else if (isdigit(c)) hasDigit = true;
        else if (!isalnum(c)) hasSpecial = true;
    }
    if (hasUpper) score++;
    if (hasDigit) score++;
    if (hasSpecial) score++;

    cout << "Сложность: ";
    if (score <= 3) cout << "Слабый\n";
    else if (score <= 5) cout << "Средний\n";
    else cout << "Сильный\n";
}

void saveToFile() {
    ofstream file("data.txt");
    if (!file) {
        cout << "Ошибка сохранения\n";
        return;
    }

    for (auto& item : repo.getAll()) {
        item->saveToFile(file);
    }
    file.close();
    cout << "Сохранено в data.txt\n";
}

void loadFromFile() {
    ifstream file("data.txt");
    if (!file) {
        cout << "Файл данных не найден. Начинаем с нуля.\n";
        return;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string type, service, username, password, extra1, extra2;
        int id;

        getline(ss, type, ',');
        ss >> id; ss.ignore();
        getline(ss, service, ',');
        getline(ss, username, ',');
        getline(ss, password, ',');
        getline(ss, extra1, ',');
        getline(ss, extra2, ',');

        if (type == "Social") {
            auto entity = make_shared<SocialPassword>(service, username, password, extra1);
            repo.add(entity);
        }
        else if (type == "Bank") {
            auto entity = make_shared<BankPassword>(service, username, password, extra1, extra2);
            repo.add(entity);
        }
    }
    file.close();
    cout << "Загружено " << repo.size() << " паролей\n";
}