cmake_minimum_required(VERSION 3.0.0)
project(CGI_CHEKUNOV VERSION 0.1.0)
message("Project ${PROJECT_NAME}:\n")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

message("Finding packages:\n")
find_package(glfw3 3.3 REQUIRED)
find_package(OpenGL REQUIRED)

message("Finding libraries:\n")
add_library("glad" "${PROJECT_SOURCE_DIR}/external/glad/src/glad.c")
include_directories("${PROJECT_SOURCE_DIR}/external/glad/include")

set(sources
    # triangle.cpp
    # test.cpp
    main.cpp
    external/imgui/imconfig.h
    external/imgui/imgui_demo.cpp
    external/imgui/imgui_draw.cpp
    external/imgui/imgui_impl_glfw.cpp
    external/imgui/imgui_impl_glfw.h
    external/imgui/imgui_impl_opengl3.cpp
    external/imgui/imgui_impl_opengl3.h
    external/imgui/imgui_internal.h
    external/imgui/imgui_tables.cpp
    external/imgui/imgui_widgets.cpp
    external/imgui/imgui.cpp
    external/imgui/imgui.h
    external/imgui/imstb_rectpack.h
    external/imgui/imstb_textedit.h
    external/imgui/imstb_truetype.h
)

message("Adding executable:\n")
add_executable(${PROJECT_NAME} ${sources})

message("Linking libraries:\n")
target_link_libraries(${PROJECT_NAME} glfw OpenGL::GL "glad")
target_link_libraries(${PROJECT_NAME} "-framework Cocoa" "-framework IOKit" "-framework CoreVideo")


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
