cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)

add_definitions(-D_DEBUG -D__STDC_CONSTANT_MACROS -D__STDC_FORMAT_MACROS -D__STDC_LIMIT_MACROS)

#find_package(BISON)
#find_package(FLEX)

#BISON_TARGET(MyParser src/parser.y ${CMAKE_CURRENT_BINARY_DIR}/parser.tab.cpp)
#FLEX_TARGET(MyScanner src/lexer.lex ${CMAKE_CURRENT_BINARY_DIR}/lex.yy.cpp)
#ADD_FLEX_BISON_DEPENDENCY(MyScanner MyParser)

add_subdirectory(PEGTL)

include_directories(include)
include_directories(PEGTL/include)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_executable(schemec src/main.cpp)
