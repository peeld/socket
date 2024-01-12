cmake_minimum_required (VERSION 3.13)
project(PeelSocket)

set(CMAKE_CXX_STANDARD 17)
set(SRCS 
	peel/net/address.cpp
	peel/net/address.h
	peel/net/defines.h
	peel/net/error.cpp
	peel/net/error.h
	peel/net/socketbase.cpp
	peel/net/socketbase.h
	peel/net/udp.cpp
	peel/net/udp.h)

set(socket_target PeelSocket)
add_library(${socket_target} ${SRCS})
