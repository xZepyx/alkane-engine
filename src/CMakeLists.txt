add_library(alkane STATIC
    external/glad.c
)

target_include_directories(alkane PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/alkane
    ${CMAKE_CURRENT_SOURCE_DIR}/external
)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

target_link_libraries(alkane
    PUBLIC
    OpenGL::GL
    glfw
)