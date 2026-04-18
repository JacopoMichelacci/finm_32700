#include <string>
#include <iostream>



struct Trade {
    std::string symbol;
    double price;

    Trade() = default;
    Trade(const std::string& s, double p) : symbol(s), price(p) {
        std::cout << "Trade created: " << symbol << "\n";
    }

    ~Trade() {
        std::cout << "Trade destroyed: " << symbol << "\n";
    }

    void print() {
        std::cout << "| Trade(" << symbol << ", " << std::to_string(price) << ") |";
    }
};

class TradeHandle {
    Trade *ptr;

public:
    TradeHandle(Trade* pointer) : ptr(pointer) {}
    ~TradeHandle() {
        std::cout << "destructor: tradehandle\n";
        delete ptr;
    }

    TradeHandle(const TradeHandle&) = delete;
    TradeHandle& operator=(const TradeHandle&) = delete;

    TradeHandle(TradeHandle&& other) : ptr(other.ptr) {
        other.ptr = nullptr;
    }

    TradeHandle& operator=(TradeHandle&& other) {
        if (this != &other) {
            delete ptr;
            ptr = other.ptr;
            other.ptr = nullptr;
        }

        return *this;
    }

    Trade* operator->() {return ptr;}
    Trade& operator*() {return *ptr;}
};

class TradeHandle {
    Trade* ptr;

public:
    TradeHandle(Trade* p);
    ~TradeHandle();
    TradeHandle(const TradeHandle&) = delete;
    TradeHandle& operator=(const TradeHandle&) = delete;
    TradeHandle(TradeHandle&& other);
    TradeHandle& operator=(TradeHandle&& other);
    Trade* operator->();
    Trade& operator*();
};


int main() {

    {
    std::cout << "\n////////////////// PART 1 //////////////////";

    // allocate trade objects on the heap and delete them
    auto *trade1 = new Trade("AAPL", 33.3);
    auto *trades = new Trade[5];

    for (int i=0; i < 5; ++i) {
        trades[i].symbol = "TSLA";
        trades[i].price = 67.7 + i;
    }

    std::cout << "Third element of the array: "; 
    trades[2].print();

    // deleting objects on the heap
    delete trade1;
    delete[] trades;
    }

    //////////////////// PART 2 ////////////////////////////////////

    {
    std::cout << "\n////////////////// PART 2 //////////////////";

    Trade* t1 = new Trade("AAPL", 150.0);
    Trade* t2 = new Trade("GOOG", 2800.0);
    delete t1;
    //delete t1; // ❌ this is wrong and will probably cause a trace trap

    Trade* t3 = new Trade("MSFT", 300.0);
    Trade *addrt3 = t3;
    t3 = new Trade("TSLA", 750.0); // ❌ this creates a memory leak as the previous t3 trade object remains in memory and we wont have a way to delete it 
                                   // unless we saved its memory address before creating a new t3 object on the heap and delete it after
    delete addrt3;
    delete t3;

    Trade *trades = new Trade[3] {
        {"NVDA", 900.0},
        {"AMZN", 3200.0},
        {"META", 250.0}
    };
    //delete trades; // ❌ this is wrong as it doesnt free the whole array on the heap and crashes at runtime

    trades[2].print();

    delete[] trades;
    }

    //////////////////// PART 3 ////////////////////////////////////

    {
    std::cout << "\n////////////////// PART 3 //////////////////";
    TradeHandle h1(new Trade("CIAO", 63.8));
    TradeHandle h2(new Trade("AU", 70.8));
    
    std::cout << "\ncall move constr: \n";
    TradeHandle h3(std::move(h2));      // move constructor
    
    std::cout << "\ncall move assignment: \n";
    h1 = std::move(h3);                 // move assignment   
    
    std::cout << "\ngoing out of scope: \n";
    }

    std::cout << "\nprogram ended successfully!";
    return 0;
}