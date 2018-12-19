project(11_texture)
set(PROJECT_SRCS ${PROJECT_SRCS} ./texture.cpp)
add_executable(${PROJECT_NAME} ${PROJECT_SRCS})
target_link_libraries(${PROJECT_NAME} ${EXTRA_LIBS})
