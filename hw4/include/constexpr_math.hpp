// making factorial, fibonacci, isodd and print_all
#pragma once

#include <type_traits> 
#include <iostream> 
#include <cmath>
using namespace std;


constexpr int factorial(int n) {
    if (n == 0) {
        return 1;
    } 
    if (n == 1) {
        return 1;
    }
    return n * factorial(n-1);
}

constexpr int fibonacci(int n){
    if (n == 0) {
        return 0;
    }
    if (n == 1){
        return 1;
    }
    return fibonacci(n - 1) + fibonacci(n - 2);
}

constexpr double price_bucket(double price){
    int scaled = static_cast<int>(price * 20); 
    return scaled / 20.0;
}

constexpr int square(int x) {
    return x * x;
}

static_assert(factorial(5) == 120, "factorial w 5 failed");
static_assert(fibonacci(7) == 13, "fib w 7 failed");
static_assert(factorial(0) == 1, "factorial w 1 failed");
static_assert(price_bucket(1.23) == 1.20, "price bucket w 1.23 failed");
static_assert(square(5) == 25, "square w 5 failed");
