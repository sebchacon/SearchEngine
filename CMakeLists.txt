cmake_minimum_required(VERSION 3.15)
project(FinalProjExamples)

# filesystem.h require C++17
set(CMAKE_CXX_STANDARD 17)

file(COPY sample_data/ DESTINATION sample_data/)

# show compiler output and enable warnings
set(CMAKE_VERBOSE_MAKEFILE ON)
add_compile_options(-Wall -Wextra -pedantic)

add_executable(rapidJSONExample rapidJSONExample.cpp)
add_executable(supersearch main.cpp DocumentParser.cpp IndexHandler.cpp porter2_stemmer.cpp QueryEngine.cpp SearchEngine.cpp document.cpp)

# this makes sure we also link rapidjson
# target_include_directories(rapidJSONExample PRIVATE rapidjson/)

set(CMAKE_VERBOSE_MAKEFILE OFF)


include(CTest)
add_executable(test_avl test_AVLTree.cpp document.cpp)
add_test(NAME test_AVLTree COMMAND test_avl)