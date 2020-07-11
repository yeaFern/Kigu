cmake_minimum_required(VERSION 2.8.12)
project(Kigu)

find_package(OpenGL)
find_package(Vulkan REQUIRED FATAL_ERROR)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

file(GLOB_RECURSE KIGU_SOURCES
    Kigu/include/*.h
    Kigu/src/*.h
    Kigu/src/*.cpp
)

foreach(_source IN ITEMS ${KIGU_SOURCES})
    get_filename_component(_source_path "${_source}" PATH)
    string(REPLACE "${CMAKE_SOURCE_DIR}" "" _group_path "${_source_path}")
    string(REPLACE "/" "\\" _group_path "${_group_path}")
    source_group("${_group_path}" FILES "${_source}")
endforeach()

file(GLOB_RECURSE EXAMPLE_SOURCES
    Example/*.h
    Example/*.cpp
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG")

add_library(${PROJECT_NAME} ${KIGU_SOURCES})
target_link_libraries(${PROJECT_NAME} ${OPENGL_gl_LIBRARY} ${Vulkan_LIBRARIES} ${CONAN_LIBS})
target_include_directories(${PROJECT_NAME} PRIVATE Kigu/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${Vulkan_INCLUDE_DIRS})

add_executable(Example ${EXAMPLE_SOURCES})
target_link_libraries(Example ${PROJECT_NAME})
target_include_directories(Example PRIVATE Kigu/include)
