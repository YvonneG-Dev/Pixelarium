cmake_minimum_required(VERSION 3.16)

project(Pixelarium VERSION 0.1 LANGUAGES CXX)

# set strict C++20 standard to allow cross platform functionality
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Qt6 REQUIRED COMPONENTS Quick)

qt_standard_project_setup(REQUIRES 6.10)

qt_add_executable(appPixelarium
    src/app/main.cpp
)

qt_add_qml_module(appPixelarium
    URI appPixelarium
    QML_FILES
        qml/Main.qml
    SOURCES
        src/model/ImageInfo.h
        src/viewmodels/ImageViewModel.h
        src/viewmodels/ImageViewModel.cpp
        src/core/ImageLoader.h
        src/core/ImageLoader.cpp
)

target_include_directories(appPixelarium PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/src/viewmodels"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/model"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/core"
)

target_include_directories(appPixelarium SYSTEM PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/third_party"
)

set_target_properties(appPixelarium PROPERTIES
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appPixelarium
    PRIVATE Qt6::Quick
)

install(TARGETS appPixelarium
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
