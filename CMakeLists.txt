# Copyright (c) 2009 Daniel Pfeifer

cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(Vera++)

set(Boost_USE_STATIC_LIBS ON)
find_package(Boost REQUIRED COMPONENTS
  filesystem
  program_options
  system
  wave
  )
find_package(Lua51 REQUIRED)

add_definitions(-DBOOST_ALL_NO_LIB=1)
if(MSVC)
  add_definitions(
    -D_CRT_SECURE_NO_WARNINGS
    -D_SCL_SECURE_NO_WARNINGS
    )
endif(MSVC)

include_directories(
  ${Boost_INCLUDE_DIRS}
  ${LUA_INCLUDE_DIR}
  luabind
  )

set(vera_src
  src/globals.hpp
  src/Interpreter.cpp
  src/Interpreter.h
  src/problem.hpp
  src/SourceLines.cpp
  src/SourceLines.h
  src/Tokens.cpp
  src/Tokens.h
  src/main.cpp
  )

set(luabind_src
  luabind/src/class_info.cpp
  luabind/src/class_registry.cpp
  luabind/src/class_rep.cpp
  luabind/src/class.cpp
  luabind/src/create_class.cpp
  luabind/src/error.cpp
  luabind/src/exception_handler.cpp
  luabind/src/function.cpp
  luabind/src/inheritance.cpp
  luabind/src/link_compatibility.cpp
  luabind/src/object_rep.cpp
  luabind/src/open.cpp
  luabind/src/pcall.cpp
  luabind/src/scope.cpp
  luabind/src/stack_content_by_name.cpp
  luabind/src/weak_ref.cpp
  luabind/src/wrapper_base.cpp
  )

source_group(vera++  FILES ${vera_src})
source_group(luabind FILES ${luabind_src})

add_executable(vera++
  ${vera_src}
  ${luabind_src}
  )

target_link_libraries(vera++
  ${LUA_LIBRARIES}
  ${Boost_LIBRARIES}
  )

add_custom_target(selfcheck
  COMMAND vera++ --root-dir=${CMAKE_SOURCE_DIR} ${vera_src}
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  )
