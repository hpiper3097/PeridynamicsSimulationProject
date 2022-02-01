cmake_minimum_required(VERSION 3.10.1)

set(projectName PeridynamicSimulation)

project (${projectName}, CXX)

add_library(Node node.cpp)

add_executable(App mesh.cpp)

target_link_libraries( App PUBLIC Node )