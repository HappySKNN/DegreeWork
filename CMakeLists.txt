cmake_minimum_required(VERSION 3.22)

project(reverse_cuthill_mckee_ordering)

find_path(HEAD /headers)
find_library(LIBS /libs)

set(Boost_INCLUDE_DIR c:/mingw/include/)
set(Boost_LIBRARY_DIR c:/mingw/lib/)
find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

add_executable(reverse source/source.cpp source/routines.cpp source/reverse_cuthill_mckee.cpp
        source/reverse_cuthill_mckee_boost_test.cpp source/king_boost_test.cpp source/approximate_minimum_degree_test.cpp)
target_link_libraries(reverse -lamd -fopenmp)
