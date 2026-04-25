#pragma once

#include <cstddef>
#include <iostream>
#include <mutex>
#include <stdexcept>

#include "generic_algorithms.hpp"

struct HeapAllocator {
    template <typename T>
    T* allocate(std::size_t n) {
        return new T[n];
    }

    template <typename T>
    void deallocate(T* ptr) {
        delete[] ptr;
    }
};

struct StackAllocator {
    template <typename T>
    T* allocate(std::size_t n) {
        return new T[n]; // fake stack allocator for assignment interface
    }

    template <typename T>
    void deallocate(T* ptr) {
        delete[] ptr;
    }
};

struct NoLock {
    void lock() {}
    void unlock() {}
};

struct MutexLock {
    void lock() {
        mtx.lock();
    }

    void unlock() {
        mtx.unlock();
    }

private:
    std::mutex mtx;
};

template <typename AllocatorPolicy, typename ThreadingPolicy>
class OrderBookBuffer {
public:
    explicit OrderBookBuffer(std::size_t capacity)
        : capacity_(capacity) {
        data_ = allocator_.template allocate<Order>(capacity_);
    }

    ~OrderBookBuffer() {
        allocator_.template deallocate<Order>(data_);
    }

    void add_order(const Order& order) {
        lock_.lock();

        if (size_cnt_ == capacity_) {
            lock_.unlock();
            throw std::length_error("OrderBookBuffer is full");
        }

        data_[size_cnt_] = order;
        ++size_cnt_;

        lock_.unlock();
    }

    void print_orders() {
        lock_.lock();

        for (std::size_t i = 0; i < size_cnt_; ++i) {
            std::cout << "Order id=" << data_[i].id
                      << ", price=" << data_[i].price
                      << ", qty=" << data_[i].qty
                      << '\n';
        }

        lock_.unlock();
    }

    Order& operator[](std::size_t i) {
        return data_[i];
    }

    const Order& operator[](std::size_t i) const {
        return data_[i];
    }

    std::size_t size() const {
        return size_cnt_;
    }

    std::size_t capacity() const {
        return capacity_;
    }

private:
    Order* data_ = nullptr;
    std::size_t capacity_;
    std::size_t size_cnt_ = 0;

    AllocatorPolicy allocator_;
    ThreadingPolicy lock_;
};