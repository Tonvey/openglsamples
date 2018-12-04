project(13_glfw_hello)
set(GLFW_PROJECT_SRCS ${GLFW_PROJECT_SRCS} ./glfw_hello.cpp)
add_executable(${PROJECT_NAME} ${GLFW_PROJECT_SRCS})
target_link_libraries(${PROJECT_NAME} ${EXTRA_LIBS})
