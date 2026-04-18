struct PriceLevel { 
    double price; 
    int quantity; 
    PriceLevel(double p, int q) : price(p), quantity(q) {}
    void add(double qty) {
        quantity += qty;
    }
    void remove(double qty) {
        quantity -= qty;
        if (quantity < 0) quantity = 0;
    }
    bool is_empty() const { 
        return quantity == 0; 
    }
};