# HFT Order Book Simulation

## Overview

This project implements a simple template-based order book simulation in C++.

The program generates random incoming orders for different tick counts, inserts them through an `OrderManager`, and runs a `MatchingEngine` to match buy and sell orders when the best bid is greater than or equal to the best ask.

Latency is measured in nanoseconds for each simulated tick.

## Architecture

- `Order.hpp`  
  Defines the templated `Order<PriceType, OrderIdType>` type.

- `OrderBook.hpp`  
  Stores buy and sell orders, tracks best bid/ask levels, and supports order book updates.

- `OrderManager.hpp`  
  Handles creation and submission of new orders into the order book.

- `MatchingEngine.hpp`  
  Matches orders when bid and ask prices cross.

- `utils/timer.hpp`  
  Measures tick-to-trade latency.

## Build and Run

Run:

```bash
./run.sh
```

The program prints minimum, maximum, and mean tick-to-trade latency.