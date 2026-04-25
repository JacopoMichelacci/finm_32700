#pragma once

#include <cstddef>


template <typename Iter, typename Pred>
Iter find_if(Iter first, Iter last, Pred predf) {
    while (first != last) {
        if (predf(*first)) {
            return first;
        }
        ++first;
    }

    return last;
}



struct Order {
    int id;
    double price;
    int qty;
};