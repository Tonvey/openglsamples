project(12_world_map)
set(PROJECT_SRCS ${PROJECT_SRCS} ./main.cpp)
add_executable(${PROJECT_NAME} ${PROJECT_SRCS})
target_link_libraries(${PROJECT_NAME} ${EXTRA_LIBS})
