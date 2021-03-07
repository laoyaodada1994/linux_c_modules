
cmake_minimum_required(VERSION 3.10)
project(sys_utils)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_C_FLAGS_DEBUG   " -g -DDEBUG -Wall -Wno-pointer-sign -O0")
set(CMAKE_C_FLAGS_RELEASE  "${CMAKE_C_FLAGS_RELEASE} -Wall  -O3")
add_subdirectory(sys_utils)
set(OUTPUT_BIN "${PROJECT_SOURCE_DIR}/output/bin")

# FIND_LIBRARY(LINK_LIB sys_log ./output/lib/)
# link_libraries("/usr/local/lib/")
include_directories(
    ${PROJECT_SOURCE_DIR}/sys_utils/include
)
aux_source_directory(${PROJECT_SOURCE_DIR} DIR_SRCS)

add_executable(main ${DIR_SRCS})
TARGET_LINK_LIBRARIES(main sys_utils sys_log)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build/)

install(TARGETS main RUNTIME DESTINATION ${OUTPUT_BIN})

enable_testing()
add_test(test1 ${OUTPUT_BIN}/main  1 2)
add_test(test2 ${OUTPUT_BIN}/main  1 2)
