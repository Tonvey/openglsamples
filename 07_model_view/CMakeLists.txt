project(07_model_view)
set(PROJECT_SRCS ${PROJECT_SRCS} ./model_view.cpp)
add_executable(${PROJECT_NAME} ${PROJECT_SRCS})
target_link_libraries(${PROJECT_NAME} ${EXTRA_LIBS})
