// making factorial, fibonacci, isodd and print_all 
#include <type_traits> 
#include <iostream> 
using namespace std;

template<int N> struct Factorial;
template<> struct Factorial<0> { static constexpr int value = 1; };
template<int N> struct Factorial { static constexpr int value = N * Factorial<N - 1>::value; };


template<int N> struct Fibonacci;
template<> struct Fibonacci<0> { static constexpr int value = 0; };
template<> struct Fibonacci<1> { static constexpr int value = 1; };
template<int N> struct Fibonacci { static constexpr int value = Fibonacci< N - 1>::value + Fibonacci<N - 2>::value; };


// Use std::enable_if, std::is_integral, etc.
template <typename T> constexpr bool is_int = std::is_integral<T>::value;
template <typename T>
typename std::enable_if<std::is_integral<T>::value, void>::type
print_if_odd(T value) {
    if (value % 2 == 1) {
        std::cout << value << std::endl;
    }
}

void print_all() { 
    cout << endl;
}

template<typename T, typename... Args> 
void print_all(T first, Args... rest) {
    cout<< first << " "; 
    print_all(rest...);
}

int main() { 
    static_assert(Factorial<5>::value == 120, "factorial w 5 failed");
    static_assert(Fibonacci<7>::value == 13, "fib w 7 failed");
    static_assert(Factorial<0>::value == 1, "factorial w 1 failed");
    static_assert(Factorial<5>::value == 120, "factorial w 5 failed");

    print_if_odd(3); 
    print_if_odd(4);
    print_all(1, 2.5, "Hi there!", 'a', 10);
    return 0; 
}