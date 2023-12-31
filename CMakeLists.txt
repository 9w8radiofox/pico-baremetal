# Set the default build type to "Debug" if it's not already specified
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Choose the type of build (Debug/Release)" FORCE)
endif()
get_filename_component(PROJECT_DIR_NAME "${CMAKE_SOURCE_DIR}" NAME)
cmake_minimum_required(VERSION 3.13)
include(pico_sdk_import.cmake)
project(${PROJECT_DIR_NAME} C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
pico_sdk_init()

# Output directory for the build artifacts
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/debug)

file(GLOB_RECURSE SOURCE_FILES "src/*.c")
file(GLOB_RECURSE HEADER_FILES "include/*.h")

add_executable( ${PROJECT_DIR_NAME}
                ${SOURCE_FILES}
                ${HEADER_FILES}
                lib/shell/src/shell.c
        )

# pull in common dependencies
target_link_libraries(${PROJECT_DIR_NAME} pico_stdlib shell)

# create map/bin/hex file etc.
pico_add_extra_outputs(${PROJECT_DIR_NAME})

add_subdirectory(lib)

# Add a custom target for cleaning
add_custom_target(clean-all
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target clean
    COMMENT "Clean everything"
)
