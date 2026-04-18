#include <iostream>

#include "core/market_events.hpp"

std::ostream& operator<<(std::ostream& os, MKT_EVENT_TYPE type) {
    switch (type) {
        case (MKT_EVENT_TYPE::SPRICE): {return os << "sprice";}
    }

    return os;
}


///////////////////////////////////////////////////////////////////////////    

std::ostream& operator<<(std::ostream& os, const SPriceEvent& e) {
    os << "| SPriceEvent(ts: " << e.ts
       << ", type: " << e.type
       << ", price: " << e.price
       << ", id: " << e.id << ") |";
    return os;
}

///////////////////////////////////////////////////////////////////////////