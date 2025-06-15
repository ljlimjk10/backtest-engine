cmake_minimum_required(VERSION 3.28)
project(backtest_engine)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(libs/OrderBook)

add_executable(backtest_engine
        main.cpp
        include/engine/data/CsvBarSource.h
        include/engine/data/Bar.h
        include/engine/data/DataLoader.h
        include/engine/data/Concepts.h
        include/engine/data/BarFeed.h
        include/engine/data/BarDispatcher.h
)

target_link_libraries(backtest_engine PRIVATE OrderBookLib)
