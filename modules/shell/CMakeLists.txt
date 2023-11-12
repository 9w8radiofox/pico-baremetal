# modules/shell/CMakeLists.txt

# Include Pico SDK import file
include(${CMAKE_CURRENT_LIST_DIR}/../../pico_sdk_import.cmake)

# Add your submodule sources
file(GLOB_RECURSE SUBMODULE_SOURCES "${CMAKE_CURRENT_LIST_DIR}/src/*.c")
file(GLOB_RECURSE SUBMODULE_HEADERS "${CMAKE_CURRENT_LIST_DIR}/include/*.h")

# Create a library (you can change STATIC to SHARED if needed)
add_library(shell STATIC
            ${SUBMODULE_SOURCES}
            ${SUBMODULE_HEADERS})

# Include the necessary Pico SDK directories
target_include_directories(shell PRIVATE ${PICO_SDK_PATH}/src/common/pico_stdio
                                         # Add other necessary include directories for the submodule
                                         )

# Link against the Pico SDK libraries
target_link_libraries(shell PRIVATE pico_stdlib)