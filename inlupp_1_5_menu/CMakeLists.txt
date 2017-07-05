cmake_minimum_required(VERSION 3.6)
project(inlupp_1_5_menu)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wpedantic")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static")

set(SOURCE_FILES main.cpp System.cpp MainMenu.cpp State.cpp)
add_executable(${CMAKE_PROJECT_NAME} ${SOURCE_FILES})

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
set(SFML_ROOT "${CMAKE_CURRENT_LIST_DIR}/SFML-2.4.2")
set(SFML_STATIC_LIBRARIES TRUE)
find_package(SFML 2 REQUIRED COMPONENTS graphics window system)
if(SFML_FOUND)
	include_directories(${SFML_INCLUDE_DIR})
	target_link_libraries(${CMAKE_PROJECT_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
else()
	message(WARNING "SFML not found")
endif()

