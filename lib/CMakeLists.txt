set(LIB_BUILD_OUT_PATH lib-build-output)

# Prepare lodepng library
if (NOT EXISTS ${CMAKE_BINARY_DIR}/../include/lodepng.h)
    execute_process(COMMAND cp lodepng/lodepng.h ../include/lodepng.h WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/../lib)
endif ()

if (NOT EXISTS ${CMAKE_BINARY_DIR}/../lib/${LIB_BUILD_OUT_PATH}/lodepng)
    execute_process(COMMAND mkdir -p ${LIB_BUILD_OUT_PATH}/lodepng WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/../lib)
endif ()

if (NOT EXISTS ${CMAKE_BINARY_DIR}/../lib/${LIB_BUILD_OUT_PATH}/lodepng/lodepng.c)
    execute_process(COMMAND cp lodepng/lodepng.cpp ${LIB_BUILD_OUT_PATH}/lodepng/lodepng.c WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/../lib)
endif ()

if (NOT EXISTS ${CMAKE_BINARY_DIR}/../lib/${LIB_BUILD_OUT_PATH}/lodepng/lodepng.h)
    execute_process(COMMAND cp lodepng/lodepng.h ${LIB_BUILD_OUT_PATH}/lodepng/lodepng.h WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/../lib)
endif ()

add_library(lodepng STATIC ${LIB_BUILD_OUT_PATH}/lodepng/lodepng.c)
