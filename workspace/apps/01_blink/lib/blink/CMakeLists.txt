# Create a static library target named "blink"
add_library(blink STATIC src/blink.c)

target_include_directories(blink PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Make sure the blink library can use Zephyr headers and definitions
target_link_libraries(blink PRIVATE zephyr_interface)