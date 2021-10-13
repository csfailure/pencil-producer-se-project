cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)
project(Pencil-Producer)

#set(CMAKE_CXX_FLAGS "-g -O0 -Wall -fprofile-arcs -ftest-coverage")
#set(CMAKE_C_FLAGS "-g -O0 -Wall -W -fprofile-arcs -ftest-coverage")
#set(CMAKE_EXE_LINKER_FLAGS "-fprofile-arcs -ftest-coverage")

# Link the curl library
set(CURL_LIBRARY "-lcurl") 


# Find the CURL library
find_package(CURL REQUIRED)

add_subdirectory(doc)
add_subdirectory(PencilProducer)
add_subdirectory(test)

#enable_testing()

