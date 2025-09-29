project(stegano C)

add_executable(${PROJECT_NAME} main.c
        encode.c
        ../include/encode.h)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_BINARY_DIR}/../include)
target_link_libraries(${PROJECT_NAME} lodepng m)