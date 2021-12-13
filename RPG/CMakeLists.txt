cmake_minimum_required(VERSION 3.14)
project(RPG_Game)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
        main.cpp
	Headers/Engine.h
        Sources/Engine.cpp
        Headers/Scenario.h
	Sources/Scenario.cpp
	Headers/Button.h
        Sources/Button.cpp
        Headers/Instance.h
        Sources/Instance.cpp
	Headers/PrimaryMenuInstance.h
	Sources/PrimaryMenuInstance.cpp
        Headers/GameInstance.h
        Sources/GameInstance.cpp
	Headers/Entity.h
        Sources/Entity.cpp
        Headers/Player.h
        Sources/Player.cpp
        Headers/PlayerAnimation.h
        Sources/PlayerAnimation.cpp
        Headers/PlayerHitbox.h
	Sources/PlayerHitbox.cpp
        Headers/PlayerMovement.h
	Sources/PlayerMovement.cpp)


add_executable(RPG_Game ${SOURCE_FILES})
include_directories(/usr/local/include)

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
include_directories(${SFML_INCLUDE_DIRS})
target_link_libraries(RPG_Game sfml-system sfml-window sfml-graphics sfml-audio sfml-network)
