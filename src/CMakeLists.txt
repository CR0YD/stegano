project(stegano C)

add_executable(${PROJECT_NAME} main.c decode.c cli.c)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_BINARY_DIR}/../include)
target_link_libraries(${PROJECT_NAME} lodepng)