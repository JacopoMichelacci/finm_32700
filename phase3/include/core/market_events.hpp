#pragma once
#include <iostream>


enum class MKT_EVENT_TYPE {
    // OHLCV,          // open, high, low, close, volume
    // QUOTE,          // bid, ask, bidsize, asksize
    SPRICE,         // simple price value
};

std::ostream& operator<<(std::ostream& os, MKT_EVENT_TYPE type);

/////////////////////////////// BASE CLASS ////////////////////////////////////////////

class MarketEvent {
public:
    long long ts;
    MKT_EVENT_TYPE type;
    int id;

    MarketEvent(long long ts_, MKT_EVENT_TYPE type_, int id_)
        : ts(ts_), type(type_), id(id_) {}

    virtual ~MarketEvent() = default;

};

///////////////////////////////////////////////////////////////////////////

/////////////////////////////// SIMPLE PRICE CLASS ////////////////////////////////////////////

class SPriceEvent : public MarketEvent {
public:
    double price;

    SPriceEvent(long long ts_, double price_, int id_ = -1)
        : MarketEvent(ts_, MKT_EVENT_TYPE::SPRICE, id_), price(price_) {}
};

std::ostream& operator<<(std::ostream& os, const SPriceEvent& e);

///////////////////////////////////////////////////////////////////////////

/////////////////////////////// SOME OTHER CLASS ////////////////////////////////////////////