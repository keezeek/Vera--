# Copyright (c) 2009 Daniel Pfeifer

cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(Vera++)

find_package(TCL)
include_directories(${TCL_INCLUDE_PATH})

set(Boost_USE_STATIC_LIBS ON)
find_package(Boost REQUIRED COMPONENTS system wave)
include_directories(${Boost_INCLUDE_DIRS})

add_definitions(-DBOOST_ALL_NO_LIB=1)
if(MSVC)
  add_definitions(
    -D_CRT_SECURE_NO_WARNINGS
    -D_SCL_SECURE_NO_WARNINGS
    )
endif(MSVC)

add_executable(vera++
  src/cpptcl-1.1.4/cpptcl.cpp
  src/Exclusions.cpp
  src/Interpreter.cpp
  src/Parameters.cpp
  src/Profiles.cpp
  src/Reports.cpp
  src/RootDirectory.cpp
  src/Rules.cpp
  src/Transformations.cpp
  src/SourceFiles.cpp
  src/SourceLines.cpp
  src/Tokens.cpp
  src/main.cpp
  )

target_link_libraries(vera++
  ${TCL_LIBRARY}
  ${Boost_LIBRARIES}
  )
