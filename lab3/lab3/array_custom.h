#pragma once
#include <iostream>

template <class T>
class array_custom {
    T* data = nullptr;
    size_t size = 0;
    size_t capacity = 0;
public:
    array_custom() {

    }

    array_custom(size_t _size, const T& standard_value) {
        if (_size == 0) data = nullptr;
        else {
            capacity = size + 5;
            data = new T[capacity];
            size = _size;
            for (size_t i = 0; i < size; i++) {
                data[i] = standard_value;
            }
        }
    }

    ~array_custom() {
        //        if (data != nullptr)
        //            delete[] data;
    }

    void clear() {
        if (data != nullptr) {
            delete[] data;
            data = nullptr;
            size = 0;
            capacity = 0;
        }
    }

    void push_back(const T& value) {
        if (size == 0) {
            capacity = 5;
            data = new T[capacity];
            data[0] = value;
            size = 1;
            return;
        }
        if (size + 1 >= capacity) { // пересоздаём
            T* backup = nullptr;
            if (size != 0) {
                backup = new T[size];
                for (size_t i = 0; i < size; i++)
                    backup[i] = data[i];
            }

            //if (data != nullptr) {
            delete[] data;
            data = nullptr;
            // }
            capacity = size + 5;
            size++;
            data = new T[capacity];
            if (size != 1) {
                for (size_t i = 0; i < size - 1; i++)
                    data[i] = backup[i];
            }
            data[size - 1] = value;

            if (size != 1) delete[] backup;
        }
        else {
            data[size] = value;
            size++;
        }
    }

    void push_unique(const T& value) {
        if (find(value) == -1) {
            push_back(value);
        }
    }

    T& operator[](size_t index) {
        if (index > size) throw std::invalid_argument("Index out of size of array_custom.");
        return data[index];
    }

    int find(const T& value) {
        for (size_t i = 0; i < size; i++) {
            if (value == data[i]) return i;
        }
        return -1;  // no such element
    }

    void print() {
        std::cout << "Array: ";
        for (size_t i = 0; i < size; i++)
            std::cout << "[" << i << "] = " << data[i] << std::endl;
    }

    size_t get_size() {
        return size;
    }
};
