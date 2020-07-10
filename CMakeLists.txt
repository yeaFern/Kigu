cmake_minimum_required(VERSION 2.8.12)
project(Kigu)

find_package(OpenGL)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

file(GLOB_RECURSE KIGU_SOURCES
    Kigu/include/*.h
    Kigu/src/*.cpp
)

file(GLOB_RECURSE EXAMPLE_SOURCES
    Example/*.h
    Example/*.cpp
)

add_library(${PROJECT_NAME} ${KIGU_SOURCES})
target_link_libraries(${PROJECT_NAME} ${OPENGL_gl_LIBRARY} ${CONAN_LIBS})
target_include_directories(${PROJECT_NAME} PRIVATE Kigu/include)

add_executable(Example ${EXAMPLE_SOURCES})
target_link_libraries(Example ${PROJECT_NAME})
target_include_directories(Example PRIVATE Kigu/include)
