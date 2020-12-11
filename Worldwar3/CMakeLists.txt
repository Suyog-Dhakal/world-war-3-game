cmake_minimum_required(VERSION 3.13)
project(stage3)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
add_executable(stage3 source/Game.cpp main.cpp source/Player.cpp source/Bullet.cpp source/ResourceHolder.cpp source/mainmenu.cpp source/Entity.cpp source/Animation.cpp source/MultiPlayerGame.cpp source/Client.cpp include/Client.h source/Server.cpp include/Server.h include/Global.h source/IpInterface.cpp include/IpInterface.h)
include_directories(stage3 include )

target_link_libraries(stage3 sfml-graphics sfml-window sfml-network sfml-audio sfml-system)
