#pragma once
#include <vector>
#include <stdexcept>

namespace PassManager {

    template<typename T>
    class Stack {
    private:
        std::vector<T> data;
    public:
        void push(const T& item) { data.push_back(item); }

        T pop() {
            if (isEmpty()) throw std::out_of_range("Stack is empty");
            T item = data.back();
            data.pop_back();
            return item;
        }

        bool isEmpty() const { return data.empty(); }
        int size() const { return (int)data.size(); }
    };

}