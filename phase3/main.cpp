#include "feed_parser.h"
#include "MarketSnapshot.h"
#include "order_manager.hpp"
#include <vector>

int main() {
    auto feed = load_feed("_data/sample_feed.txt");

    MarketSnapshot snapshot;
    OrderManager order_manager;

    for (const auto& event : feed) {
        event.print();

        // Integrate with your components:
        if (event.type == FeedType::BID) {
            snapshot.update_bid(event.price, event.quantity);
        } else if (event.type == FeedType::ASK) {
            snapshot.update_ask(event.price, event.quantity);
        } else if (event.type == FeedType::EXECUTION) {
            order_manager.handle_fill(event.order_id, event.quantity);
        }
    }

    return 0;
}