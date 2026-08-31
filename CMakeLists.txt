cmake_minimum_required(VERSION 4.4.0)
project(Vortex LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB imgui_sources CONFIGURE_DEPENDS imgui/*.cpp)
add_library(imguilib
    ${imgui_sources}
    imgui/backends/imgui_impl_win32.cpp
    imgui/backends/imgui_impl_dx11.cpp
    imgui/misc/cpp/imgui_stdlib.cpp
)
target_include_directories(imguilib PUBLIC imgui)

add_subdirectory(klibrary)
target_link_libraries(klibrarylib PUBLIC imguilib)

file(GLOB_RECURSE vortex_sources CONFIGURE_DEPENDS source/*.cpp)
add_executable(vortex ${vortex_sources})
target_link_libraries(vortex PUBLIC klibrarylib)
target_include_directories(vortex PUBLIC source)
set_target_properties(vortex PROPERTIES
    DEBUGGER_WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/workdir)
