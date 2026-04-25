#pragma once

#include <cstddef>
#include <stdexcept>

template <typename T, std::size_t N>
class StaticVector {
public:

    StaticVector() = default;

    void push_back(T val) {
        if (size_cnt == N) {throw std::length_error("StaticVector reached max size and element cannot be pushed back");}

        buffer[size_cnt] = val;
        ++size_cnt;
    }

    std::size_t size() const {
        return size_cnt;
    }
    std::size_t capacity() const {
        return N;
    }


    // iterators
    T* begin() {
        return &(buffer[0]);
    }

    T* end() {
        return &(buffer[size_cnt]);
    }

    // indexing operator
    T& operator[](std::size_t i) {
        return buffer[i];
    }

private:
    T buffer[N];
    std::size_t size_cnt = 0;
};