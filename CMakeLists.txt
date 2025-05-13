# Minimum CMake, just use the latest
cmake_minimum_required(VERSION 3.31)

project(foxxbox VERSION 1.0 DESCRIPTION "A c++ discord bot")

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# create the executable
add_executable(${PROJECT_NAME}
  src/main.cpp
)

find_package(DPP REQUIRED)

target_link_libraries(${PROJECT_NAME}
  ${DPP_LIBRARIES}
)

target_include_directories(${PROJECT_NAME} PRIVATE
  ${DPP_LIBRARIES}
)

set_target_properties(${PROJECT_NAME} PROPERTIES
  CXX_STANDARD 20
  CXX_STANDARD_REQURIED ON
)
