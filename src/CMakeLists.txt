project(stegano C)

add_executable(${PROJECT_NAME} main.c cli.c)
target_link_libraries(${PROJECT_NAME} lodepng)