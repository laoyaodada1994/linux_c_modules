
cmake_minimum_required(VERSION 3.10)
project(sys_log)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -Wall -O2")
set(OUTPUT_BIN "${PROJECT_SOURCE_DIR}/output/bin")
add_subdirectory(sys_log)

# link_libraries("${PROJECT_SOURCE_DIR}/build/sys_log/")
include_directories(
    ${PROJECT_SOURCE_DIR}/sys_log/include
)
aux_source_directory(${PROJECT_SOURCE_DIR} DIR_SRCS)
add_executable(main ${DIR_SRCS})
TARGET_LINK_LIBRARIES(main sys_log)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build/)
# # 安装main是可执行文件
install(TARGETS main RUNTIME DESTINATION ${OUTPUT_BIN})

# ### Testing 指令:make test#
enable_testing()
add_test(test1 ${OUTPUT_BIN}/main  1 2)
add_test(test2 ${OUTPUT_BIN}/main  1 2)
