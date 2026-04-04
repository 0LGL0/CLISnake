cmake_minimum_required(VERSION 4.1)
project(CLISnake)

set(CMAKE_CXX_STANDARD 20)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

add_library(Core STATIC
  "${CMAKE_CURRENT_SOURCE_DIR}/src/Input.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/Framebuffer.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/Snake.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/Apple.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/Game.cpp"
)

add_executable(CLISnake main.cpp)

target_include_directories(Core PUBLIC
  "${CMAKE_CURRENT_SOURCE_DIR}/src"
)

target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC
  Core
)
