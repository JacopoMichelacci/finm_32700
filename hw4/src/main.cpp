#include <iostream>
#include <chrono>

#include "generic_algorithms.hpp"
#include "StaticVector.hpp"
#include "metaprogramming.hpp"
#include "constexpr_math.hpp"
#include "OrderBookBuffer.hpp"



int main() {

    std::cout << "\n############ PART 1 ############\n";
    cout << "testing factorial logic:" << endl; 

    cout << factorial(0) << endl; 
    cout << factorial(2) << endl; 
    cout << factorial(4) << endl; 
    cout << factorial(10) << endl; 

    cout << endl; 
    cout << endl; 
    cout << "testing fibonacci logic" << endl; 

    cout << fibonacci(0) << endl; 
    cout << fibonacci(1) << endl; 
    cout << fibonacci(5) << endl; 
    cout << fibonacci(7) << endl; 
    cout << fibonacci(30) << endl; 

    cout << endl; 
    cout << endl; 

    cout << "testing price bucket" << endl; 
    cout << price_bucket(102.2) << endl;
    cout << price_bucket(2.2) << endl;
    cout << price_bucket(0.0000002) << endl;

    cout << endl; 
    cout << endl; 
    
    cout << "testing square logic" << endl; 
    cout << square(1) << endl;
    cout << square(2) << endl;
    cout << square(4) << endl;
    cout << square(10) << endl;
    cout << square(16) << endl;


    std::cout << "\n############ PART 2 ############\n";

    static_assert(Factorial<5>::value == 120, "factorial w 5 failed");
    static_assert(Fibonacci<7>::value == 13, "fib w 7 failed");
    static_assert(Factorial<0>::value == 1, "factorial w 1 failed");
    static_assert(Factorial<5>::value == 120, "factorial w 5 failed");

    print_if_odd(3); 
    print_if_odd(4);
    print_all(1, 2.5, "Hi there!", 'a', 10);


    std::cout << "\n############ PART 3 ############\n";

    StaticVector<Order, 100> ord_vector;
    for (int i=0; i < 100; ++i) {
        double price = 100 + ((i * 42) % 50) + (i % 99) * 0.1;
        int idx = i % 10;
        int qty = static_cast<int>(price) % 125;

        ord_vector.push_back(Order(idx, price, qty));
    }
    std::cout << "price of order 78: " << ord_vector[78].price << "\n";


    std::cout << "\n############ PART 4 ############\n";

    OrderBookBuffer<StackAllocator, NoLock> book1(10);
    OrderBookBuffer<HeapAllocator, MutexLock> book2(10);

    book1.add_order(ord_vector[77]);
    book1.add_order(ord_vector[78]);

    book1.print_orders();

    std::cout << "\nprogram ran successfully!\n";
    return 0;
}