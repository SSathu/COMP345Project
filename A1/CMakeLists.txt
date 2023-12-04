cmake_minimum_required(VERSION 3.26)
project(a1_335_p5)

set(CMAKE_CXX_STANDARD 17)

add_executable(MainDriver

#   GameEngine/GameEngineDriver.cpp
    GameEngine/GameEngine.h
    GameEngine/GameEngine.cpp

#   Map/MapDriver.h
    Map/Map.cpp
    Map/Map.h

#   Orders/OrdersDriver.cpp
    Orders/Orders.cpp
    Orders/Orders.h

#   Cards/CardDriver.cpp
    Cards/Cards.h
    Cards/Cards.cpp

#   Player/PlayerDriver.cpp
    Player/Player.h
    Player/Player.cpp

#   CommandProcessing/CommandProcessingDriver.cpp
    CommandProcessing/CommandProcessing.cpp
    CommandProcessing/CommandProcessing.h

    Utils/GameUtils.cpp
    Utils/GameUtils.h

        LogObserver/LoggingObserver.h
        LogObserver/LoggingObserver.cpp
#  LogObserver/LoggingObserverDriver.cpp

        MainDriver.cpp

 "PlayerStrategies/PlayerStrategies.cpp" "PlayerStrategies/PlayerStrategies.h")