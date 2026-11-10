cmake_minimum_required(VERSION 3.16)

project(PixelariumTests LANGUAGES CXX)

# set strict C++20 standard to allow cross platform functionality
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 1. Include GoogleTest locally (bypasses mac network/sandbox issues)
set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
add_subdirectory(googletest)

# 2. Define the test executable and include source files
add_executable(unit_tests
    unit-tests/ImageLoaderTest.cpp
    ../src/core/ImageLoader.cpp
)

# 3. Set search paths for the compiler
target_include_directories(unit_tests PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/../src/viewmodels"
    "${CMAKE_CURRENT_SOURCE_DIR}/../src/model"
    "${CMAKE_CURRENT_SOURCE_DIR}/../src/core"
    
    # Paths pointing to your local googletest directory
    "${CMAKE_CURRENT_SOURCE_DIR}/googletest/googletest/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/googletest/googlemock/include"

    # Tell the test runner where to find external libraries like stb_image.h
    "${CMAKE_CURRENT_SOURCE_DIR}/../third_party"
)

# 4. Link against the local GoogleTest targets
target_link_libraries(unit_tests PRIVATE 
    gtest_main
    gtest
)

# 5. Register within CMake's test runner
add_test(NAME CppUnitTests COMMAND unit_tests)