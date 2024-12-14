# Minimum CMake version
cmake_minimum_required(VERSION 3.16)

# Project name and version
project(PDFImageExtractor VERSION 1.0 LANGUAGES C)

# If you're using vcpkg, specify the toolchain file
set(VCPKG_ROOT "<path-to-vcpkg>")
set(CMAKE_TOOLCHAIN_FILE "${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")

# Find the required packages
find_package(PkgConfig REQUIRED)
pkg_check_modules(POPPLER REQUIRED poppler)

# Include directories and link directories for Poppler
include_directories(${POPPLER_INCLUDE_DIRS})
link_directories(${POPPLER_LIBRARY_DIRS})
add_definitions(${POPPLER_CFLAGS_OTHER})

# Define the executable (replace "main.c" with your actual source file(s))
add_executable(PDFImageExtractor main.c)

# Link the Poppler libraries to the target
target_link_libraries(PDFImageExtractor ${POPPLER_LIBRARIES})

