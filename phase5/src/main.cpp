#include <iostream>

#include "../include/order_book.hpp"
#include "../include/order.hpp"
#include "../include/timer.hpp"
#include "../include/stress_test.hpp"

#include "../tests/test_order_book.hpp"



int main() {

    OrderBook order_book;

    std::string time_measure = "nanoseconds";
    Timer timer(time_measure);

    {
    long long elapsed = timer.f_elapse([&](){order_book.addOrder(Order("ciao1", 100.1, 10, true));}, 100);

    std::cout << "Time Elapsed for 1 add order: " << elapsed << time_measure << std::endl;
    }


    UnitTest utest;
    utest.testAddOrder();

    {
    std::size_t n_orders = 100;
    long long elapsed = timer.f_elapse([&](){stressTest(order_book, 100);}, 100);

    std::cout << "Time Elapsed for " << n_orders << " orders in stress test: " << elapsed << time_measure << std::endl;
    }

    return 0;
}