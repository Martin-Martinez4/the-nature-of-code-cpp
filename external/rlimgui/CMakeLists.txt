cmake_minimum_required(VERSION 3.11)

project(rlimgui)

set(rlImGui_CPP_SRC_DIR "${CMAKE_CURRENT_LIST_DIR}")

set(rlImGui_BUILD_SOURCES
    "${rlImGui_CPP_SRC_DIR}/rlImGui.cpp"
    )

add_library(rlimgui STATIC "${rlImGui_BUILD_SOURCES}")
target_compile_definitions(rlimgui PUBLIC NO_FONT_AWESOME)
target_include_directories(rlimgui PUBLIC "${rlImGui_CPP_SRC_DIR}")
target_link_libraries(rlimgui PUBLIC imgui raylib)
