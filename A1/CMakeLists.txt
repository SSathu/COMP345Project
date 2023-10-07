cmake_minimum_required(VERSION 3.26)
project(a1_335_p5)

set(CMAKE_CXX_STANDARD 17)

add_executable(a1_335_p5
        GameEngine/GameEngine.h
        GameEngine/GameEngine.cpp
        GameEngine/GameEngineDriver.cpp
        Map/MapDriver.h
        Map/MapDriver.cpp
        Orders/Orders.cpp
        Map/Map.cpp
        Map/Map.h
        Orders/OrdersDriver.cpp
        Orders/Orders.h
        Cards/Cards.cpp
        Cards/Cards.h
        Cards/CardDriver.cpp)
