cmake_minimum_required(VERSION 3.15)
project(kernel)

set(INCLUDE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/include)

file(GLOB_RECURSE SOURCES "src/*.cpp")
include_directories(${INCLUDE_PATH}
${INCLUDE_PATH}/state)

add_library(${PROJECT_NAME} STATIC ${SOURCES})

# Specify the include directories for the library
target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_PATH})
target_link_libraries(${PROJECT_NAME} PUBLIC 
	freertos_kernel
	planner
	com-if)