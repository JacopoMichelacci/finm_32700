#pragma once

#include <vector>
#include <string>
#include <optional>
#include <functional>
#include <algorithm>

struct Entry {
    std::string key;
    double value = 0.0;
    bool occupied = false;
    int psl = 0; // probe sequence length
};

class RobinHoodHash {
private:
    std::vector<Entry> table;
    size_t tableSize;
    size_t count;

    size_t hashFunction(const std::string& key) const {
        return std::hash<std::string>{}(key) % tableSize;
    }

public:
    explicit RobinHoodHash(size_t size = 1024)
        : tableSize(size), count(0), table(size) {}

    void insert(const std::string& key, double value) {
        Entry curr{key, value, true, 0};

        size_t idx = hashFunction(key);

        while (true) {
            if (!table[idx].occupied) {
                table[idx] = curr;
                count++;
                return;
            }

            if (table[idx].key == key) {
                table[idx].value = value;
                return;
            }

            if (table[idx].psl < curr.psl) {
                std::swap(table[idx], curr);
            }

            curr.psl++;
            idx = (idx + 1) % tableSize;
        }
    }

    std::optional<double> find(const std::string& key) const {
        size_t idx = hashFunction(key);
        int dist = 0;
        while (table[idx].occupied) {

            if (table[idx].key ==key) {
                return table[idx].value;
            }

            if (table[idx].psl< dist) {
                return std::nullopt;
            }

            idx = (idx + 1) % tableSize;
            dist++;
        }
        return std::nullopt;
    }

    void erase(const std::string& key) {
        size_t idx = hashFunction(key);
        int dist = 0;
        while (table[idx].occupied) {
            if (table[idx].key == key) {

                table[idx].occupied = false;
                count--;

                size_t next = (idx + 1) % tableSize;

                while (table[next].occupied) {

                    if (table[next].psl == 0) break;

                    table[idx] = table[next];
                    table[idx].psl--;

                    table[next].occupied = false;

                    idx = next;
                    next = (next + 1) % tableSize;
                }

                return;
            }
            if (table[idx].psl < dist) {
                return;
            }

            idx = (idx + 1) % tableSize;
            dist++;
        }
    }
};