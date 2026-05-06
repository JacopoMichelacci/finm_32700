#include <iostream>
#include <vector>


#include "data/generators/gen_sprice.hpp"



int main() {
    int nticks = 100;
    std::vector<SPriceEvent> data; 
    
    data = gen_sprice_gbm(5, nticks, 100.0, 0.01, 0.5, 10);


    for (auto i : data) {
        std::cout << i << "\n";
    }

    return 0;
}