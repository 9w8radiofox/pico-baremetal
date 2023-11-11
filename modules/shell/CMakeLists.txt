# CMakeLists.txt in modules/shell directory

# Add the source files for the shell module
add_library(shell
    src/shell.c
    # Add other source files if any
)

# Add include directories for the shell module
target_include_directories(shell PUBLIC include)

# Link the shell module with any dependencies
# target_link_libraries(shell PRIVATE <dependency_library>)