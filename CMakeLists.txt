cmake_minimum_required(VERSION 3.13)
project(OpenGL_Engine)



set(CMAKE_CXX_STANDARD 14)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

find_package(PkgConfig REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)
include_directories(${GLFW_INCLUDE_DIRS})
find_package(SOIL REQUIRED)
find_package(GLM REQUIRED)


add_executable(OpenGL_Engine main.cpp Engine.cpp 
                                Engine.h 
                                Graphics/Shaders.cpp 
                                Graphics/Shaders.h
                                Camera.hpp
                                Camera.cpp)
target_link_libraries(OpenGL_Engine ${OPENGL_LIBRARIES})
target_link_libraries(OpenGL_Engine ${GLFW_LIBRARIES})
target_link_libraries(OpenGL_Engine ${GLEW_LIBRARIES})
target_link_libraries(OpenGL_Engine ${SOIL_LIBRARIES})
target_link_libraries(OpenGL_Engine ${GLM_LIBRARIES})

set (source "${CMAKE_SOURCE_DIR}/Resources")
set (destination "${CMAKE_CURRENT_BINARY_DIR}/Resources")
add_custom_command(
        TARGET OpenGL_Engine POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E create_symlink ${source} ${destination}
        DEPENDS ${destination}
        COMMENT "symbolic link resources folder from ${source} => ${destination}"
)
