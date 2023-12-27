project(StringSorter)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")
set(SRC_LIST ./source/String.cpp ./source/main.cpp)
add_executable(${PROJECT_NAME} ${SRC_LIST})