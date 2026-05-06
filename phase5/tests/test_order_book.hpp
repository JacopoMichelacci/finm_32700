#include <cassert>

#include "../include/order_book.hpp"
#include "../include/order.hpp"

class UnitTest {
public:
    void testAddOrder() {
        OrderBook book;

        book.addOrder(Order("ORD001", 50.10, 100, true));
        
        assert(book.get_order("ORD001") == true);  // Order should exist
    }
};