# Minimum CMake version
cmake_minimum_required(VERSION 3.22.0)

# Locate the Zephyr RTOS source
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

# Define the project metadata
project(blink VERSION 1.0 DESCRIPTION "Blinking LED with Hello World" LANGUAGES C)

# Include the library (via directory)
add_subdirectory(lib/blink)

# Add the main application source file
target_sources(app PRIVATE src/main.c)

# Link the blink library to the main Zephyr app
target_link_libraries(app PRIVATE blink)
