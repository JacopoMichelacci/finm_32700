cmake_minimum_required(VERSION 3.20)
project(hw2)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


add_executable(
    ${PROJECT_NAME}
    main.cpp

    src/strategies/strategy_base.cpp
    
    src/core/market_events.cpp
    src/core/order_event.cpp

    src/data/generators/gen_sprice.cpp


    src/strategies/ma_cross.cpp
)


target_include_directories(
    ${PROJECT_NAME}
    PRIVATE
    include
)