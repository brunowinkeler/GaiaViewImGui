file(GLOB_RECURSE GAIAVIEW_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# Create executable
add_executable(${PROJ_NAME} ${GAIAVIEW_SOURCES})

# Link libraries
target_link_libraries(${PROJ_NAME} PRIVATE
    SDL3::SDL3
    imgui
    implot
)