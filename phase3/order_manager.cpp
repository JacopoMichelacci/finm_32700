// order_manager.cpp
#include "order_manager.hpp"

int OrderManager::place_order(Side side, double price, int qty) {
    int id = next_id++;

    auto ord = std::make_unique<MyOrder>();
    ord->id = id;
    ord->side = side;
    ord->price = price;
    ord->quantity = qty;

    orders[id] = std::move(ord);
    return id;
}

void OrderManager::cancel(int id) {
    auto it = orders.find(id);
    if (it == orders.end()) return;

    it->second->status = OrderStatus::Cancelled;
    orders.erase(it); // unique_ptr cleans up automatically
}

void OrderManager::handle_fill(int id, int filled_qty) {
    auto it = orders.find(id);
    if (it == orders.end()) return;

    MyOrder& ord = *(it->second);
    ord.filled += filled_qty;

    if (ord.filled >= ord.quantity) {
        ord.filled = ord.quantity;
        ord.status = OrderStatus::Filled;
        orders.erase(it); // fully done, remove from active orders
    } else {
        ord.status = OrderStatus::PartiallyFilled;
    }
}

void OrderManager::print_active_orders() const {
    for (const auto& [id, ord] : orders) {
        std::cout
            << "id=" << ord->id
            << " side=" << (ord->side == Side::BUY ? "BUY" : "SELL")
            << " price=" << ord->price
            << " qty=" << ord->quantity
            << " filled=" << ord->filled
            << " status=";

        switch (ord->status) {
            case OrderStatus::New:
                std::cout << "New";
                break;
            case OrderStatus::Filled:
                std::cout << "Filled";
                break;
            case OrderStatus::PartiallyFilled:
                std::cout << "PartiallyFilled";
                break;
            case OrderStatus::Cancelled:
                std::cout << "Cancelled";
                break;
        }

        std::cout << "\n";
    }
}