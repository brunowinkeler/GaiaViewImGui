# Add SDL3 as subdirectories
add_subdirectory(SDL EXCLUDE_FROM_ALL)
# Include directories
include_directories(
    SDL/include
)

# Add imgui files
set(IMGUI_LIB_NAME imgui)
file(GLOB IMGUI_SOURCES 
        ${IMGUI_LIB_NAME}/*.cpp
        ${IMGUI_LIB_NAME}/backends/imgui_impl_sdl3.cpp
        ${IMGUI_LIB_NAME}/backends/imgui_impl_sdlrenderer3.cpp)
file(GLOB IMGUI_HEADERS 
        ${IMGUI_LIB_NAME}/*.h
        ${IMGUI_LIB_NAME}/backends/imgui_impl_sdl3.h
        ${IMGUI_LIB_NAME}/backends/imgui_impl_sdlrenderer3.h)
add_library(${IMGUI_LIB_NAME} STATIC ${IMGUI_SOURCES} ${IMGUI_HEADERS})
target_link_libraries(${IMGUI_LIB_NAME} PUBLIC SDL3::SDL3)
target_include_directories(${IMGUI_LIB_NAME}
    PUBLIC
        ${IMGUI_LIB_NAME}/
        ${IMGUI_LIB_NAME}/backends/
)

# Add implot files
set(IMPLOT_LIB_NAME implot)
file(GLOB IMPLOT_SOURCES ${IMPLOT_LIB_NAME}/*.cpp)
file(GLOB IMPLOT_HEADERS ${IMPLOT_LIB_NAME}/*.h)
add_library(${IMPLOT_LIB_NAME} STATIC ${IMPLOT_SOURCES} ${IMPLOT_HEADERS})
target_link_libraries(${IMPLOT_LIB_NAME} PUBLIC ${IMGUI_LIB_NAME})
target_include_directories(${IMPLOT_LIB_NAME}
    PUBLIC
        ${IMPLOT_LIB_NAME}/
)
