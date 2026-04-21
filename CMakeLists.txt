cmake_minimum_required(VERSION 4.1)
project(CLISnake)

set(CMAKE_CXX_STANDARD 20)

find_package(EnTT REQUIRED)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

add_library(Core STATIC
  "${CMAKE_CURRENT_SOURCE_DIR}/src/Framework/Input.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/Framework/Framebuffer.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/Apple.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/Game.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/Framework/Time.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/Framework/EngineManager.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/Framework/Scene.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/Framework/World.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/Framework/Systems/MovementSystem.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/Systems/SnakeMovementSystem.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/SnakeFactory.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/Framework/SystemManager.cpp"
)

target_include_directories(Core PUBLIC
  "${CMAKE_CURRENT_SOURCE_DIR}/src"
)

target_link_libraries(Core PUBLIC
  EnTT::EnTT
)

add_executable(CLISnake main.cpp)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE
  Core
)
