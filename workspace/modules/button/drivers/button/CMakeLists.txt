# Declates the current directory as a Zephyr library
# If no name is given, the name is derived from the directory name
zephyr_library()

zephyr_library_sources(
  button.c
)

zephyr_include_directories(.)