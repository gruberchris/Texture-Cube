cmake_minimum_required(VERSION 3.28)
project(opengl-macos-project-template)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE SOURCE_FILES src/*.cpp)

include_directories(
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/libs
        ${PROJECT_SOURCE_DIR}/libs/glfw-3.4/include
        ${PROJECT_SOURCE_DIR}/libs/glad/include
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${PROJECT_SOURCE_DIR}/libs/glad/src/glad.c)

if(APPLE AND CMAKE_SYSTEM_PROCESSOR STREQUAL "arm64")
    set(GLFW_LIB_PATH ${PROJECT_SOURCE_DIR}/libs/glfw-3.4/lib-arm64/libglfw.3.dylib)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -arch arm64")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -arch arm64")
elseif(APPLE AND CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64")
    set(GLFW_LIB_PATH ${PROJECT_SOURCE_DIR}/libs/glfw-3.4/lib-x86_64/libglfw.3.dylib)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -arch x86_64")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -arch x86_64")
endif()

target_link_libraries(${PROJECT_NAME}
        ${GLFW_LIB_PATH}
        "-framework OpenGL"
        "-framework Cocoa"
        "-framework IOKit"
        "-framework CoreVideo"
)

# Copy the shaders directory to the output directory
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/shaders $<TARGET_FILE_DIR:${PROJECT_NAME}>/shaders)

# Define shader files
file(GLOB SHADERS
        "${PROJECT_SOURCE_DIR}/shaders/vertex/*.glsl"
        "${PROJECT_SOURCE_DIR}/shaders/fragment/*.glsl"
        "${PROJECT_SOURCE_DIR}/shaders/geometry/*.glsl"
)

# Add an install target to copy shaders
install(TARGETS ${PROJECT_NAME} DESTINATION bin)
install(FILES ${SHADERS} DESTINATION shaders)