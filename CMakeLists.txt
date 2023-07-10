cmake_minimum_required (VERSION 3.13)
project(PeelSocket)

set(CMAKE_CXX_STANDARD 17)
set(SRCS 
	peel/socket/address.cpp
	peel/socket/address.h
	peel/socket/defines.h
	peel/socket/error.cpp
	peel/socket/error.h
	peel/socket/socketbase.cpp
	peel/socket/socketbase.h
	peel/socket/udp.cpp
	peel/socket/udp.h)

set(socket_target PeelSocket)
add_library(${socket_target} ${SRCS})
