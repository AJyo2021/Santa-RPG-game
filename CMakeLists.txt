cmake_minimum_required(VERSION 3.12)

project(SantaGame C)

set(SOURCES
    ${CMAKE_SOURCE_DIR}/src/santa.c
)

include_directories(
    ${CMAKE_SOURCE_DIR}/include
)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

# List of asset files in the assets directory
file(GLOB ASSET_FILES ${CMAKE_SOURCE_DIR}/assets/*)

# Copy each asset to the build directory
foreach(asset ${ASSET_FILES})
    configure_file(${asset} ${CMAKE_BINARY_DIR}/assets/ COPYONLY)
endforeach()

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} SDL2 SDL2_image SDL2_ttf SDL2_mixer)

set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)