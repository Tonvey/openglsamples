project(10_lighting_model)
set(PROJECT_SRCS ${PROJECT_SRCS} ./lighting_model.c)
add_executable(${PROJECT_NAME} ${PROJECT_SRCS})
target_link_libraries(${PROJECT_NAME} ${EXTRA_LIBS})
