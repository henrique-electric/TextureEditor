cmake_minimum_required(VERSION 3.20)

project(textureEditor)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find required packages
find_package(SDL3 REQUIRED)
find_package(SDL3_image REQUIRED)

# Option 2: If using fastgltf as a subdirectory (uncomment if fastgltf is in a subdirectory)
# add_subdirectory(external/fastgltf)

# Create executable
add_executable(${PROJECT_NAME}
    src/main.cpp
)

set(IMGUI_SOURCES
    external/imgui/backends/imgui_impl_sdl3.cpp
    external/imgui/backends/imgui_impl_sdlrenderer3.cpp
    external/imgui/backends/imgui_impl_vulkan.cpp

    external/imgui/imgui.cpp
    external/imgui/imgui_demo.cpp
    external/imgui/imgui_draw.cpp
    external/imgui/imgui_tables.cpp
    external/imgui/imgui_widgets.cpp)

# Add Dear ImGui sources (adjust paths as needed)
add_library(imgui
    ${IMGUI_SOURCES}
)

set(IMGUI_INCLUDES
    ./external/imgui/
    ./external/imgui/backends/)

message(STATUS "imgui headers found: ${IMGUI_INCLUDES}")
message(STATUS "imgui sources found: ${IMGUI_SOURCES}")

target_include_directories(imgui PUBLIC ./include imgui ./external/imgui/backends ./external/imgui ./external)

# Link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE
    SDL3
    SDL3_image
    imgui
)

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${IMGUI_INCLUDES}
)

