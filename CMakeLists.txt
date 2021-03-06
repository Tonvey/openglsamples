cmake_minimum_required(VERSION 3.2)
project(StudyOpenGL)
set(CMAKE_CXX_STANDARD 11)
add_definitions(-g)

find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)
pkg_search_module(GLEW REQUIRED glew)
pkg_search_module(MINIZIP REQUIRED minizip)
include_directories(${GLFW_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS})
link_directories(${GLFW_LIBRARY_DIRS} ${GLEW_LIBRARY_DIRS} ${MINIZIP_LIBRARY_DIRS})
SET(EXTRA_LIBS ${GLFW_LIBRARIES} ${GLEW_LIBRARIES} assimp)

IF(APPLE)
set(CMAKE_MACOSX_RPATH 1)
ENDIF (APPLE)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

include_directories(./3rdparty/assimp/include)
include_directories(./3rdparty/stb)
include_directories(./3rdparty/glm)

IF(APPLE)
    FIND_LIBRARY(GLUT_LIBRARY GLUT )
    FIND_LIBRARY(OpenGL_LIBRARY OpenGL )
    SET(EXTRA_LIBS ${EXTRA_LIBS} ${GLUT_LIBRARY} ${OpenGL_LIBRARY})
ENDIF (APPLE)

IF(CMAKE_SYSTEM_NAME MATCHES "Linux")
    FIND_PACKAGE(GLUT REQUIRED)
    pkg_search_module(GLU REQUIRED glu)
    pkg_search_module(OPENGL REQUIRED gl)
    SET(EXTRA_LIBS ${EXTRA_LIBS} ${GLU_LIBRARIES} ${GLUT_LIBRARIES} ${OPENGL_LIBRARIES} m)
ENDIF(CMAKE_SYSTEM_NAME MATCHES "Linux")

# TODO 这里有点乱,要调整,先将多个公共文件创建成为库,然后再连接给所有demo
include_directories(./common/)
file(GLOB FRAME_LIB_SRCS ./common/*.cpp)
add_library(sframe ${FRAME_LIB_SRCS})
target_link_libraries(sframe ${EXTRA_LIBS})
SET(EXTRA_LIBS ${EXTRA_LIBS} sframe)

add_subdirectory(./3rdparty/assimp)

add_definitions(-DGL_SILENCE_DEPRECATION -DSTB_IMAGE_IMPLEMENTATION)
add_subdirectory(./samples/)
