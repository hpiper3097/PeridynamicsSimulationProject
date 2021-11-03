cmake_minimum_required(VERSION 3.10.1)

project (PD_Sim, CXX)

add_library(Mesh STATIC mesh.cpp)
add_library(Parser STATIC parser.cpp)

target_link_libraries( Mesh
	PRIVATE Parser
	)

add_executable(PD_Sim test.cpp)

target_link_libraries( PD_Sim
	PUBLIC Mesh
	)
