project(stegano C)

add_executable(${PROJECT_NAME} main.c cli.c encode.c decode.c)
target_link_libraries(${PROJECT_NAME} lodepng m)
