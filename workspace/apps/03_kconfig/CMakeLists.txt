cmake_minimum_required(VERSION 3.20.0)

set(ZEPHYR_EXTRA_MODULES "${CMAKE_SOURCE_DIR}/../../modules/say_hello")

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

project(random VERSION 1.0 DESCRIPTION "Random number generation example" LANGUAGES C)

target_sources(app PRIVATE src/main.c)