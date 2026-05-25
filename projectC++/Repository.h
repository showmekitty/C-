#pragma once
#include <vector>
#include <memory>
#include <algorithm>
#include <string>

namespace PassManager {

    template<typename T>
    class Repository {
    private:
        std::vector<std::shared_ptr<T>> items;
    public:
        void add(std::shared_ptr<T> item) { items.push_back(item); }

        void remove(int id) {
            items.erase(std::remove_if(items.begin(), items.end(),
                [id](std::shared_ptr<T> item) { return item->getId() == id; }), items.end());
        }

        std::shared_ptr<T> findById(int id) {
            auto it = std::find_if(items.begin(), items.end(),
                [id](std::shared_ptr<T> item) { return item->getId() == id; });
            if (it != items.end()) return *it;
            return nullptr;
        }

        std::vector<std::shared_ptr<T>> findByService(const std::string& query) {
            std::vector<std::shared_ptr<T>> result;
            for (auto& item : items) {
                if (item->getService().find(query) != std::string::npos) {
                    result.push_back(item);
                }
            }
            return result;
        }

        auto begin() { return items.begin(); }
        auto end() { return items.end(); }
        size_t size() const { return items.size(); }
        std::vector<std::shared_ptr<T>>& getAll() { return items; }
    };

}