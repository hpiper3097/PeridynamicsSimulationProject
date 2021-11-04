cmake_minimum_required(VERSION 3.10.1)

set(projectName PD_Sim)

project (${projectName}, CXX)

add_library(Mesh mesh.cpp)
add_library(Parser parser.cpp)

target_link_libraries( Mesh PRIVATE Parser )

add_executable(PD_Sim_Serial test.cpp)

target_link_libraries( PD_Sim_Serial PUBLIC Mesh )
