set(OUTPUT_LIB "output/lib")

include_directories(
    ${PROJECT_SOURCE_DIR}/sys_log/include
)

aux_source_directory(${PROJECT_SOURCE_DIR}/sys_log/ SYS_LOG_SRCS)

link_directories(/usr/local/lib)

add_library(sys_log SHARED ${SYS_LOG_SRCS})
add_library(sys_log2 STATIC ${SYS_LOG_SRCS})
set_target_properties(sys_log2 PROPERTIES OUTPUT_NAME "sys_log")
set_target_properties (sys_log PROPERTIES VERSION 1.4 SOVERSION 1)

set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build/sys_log/)

install(TARGETS sys_log sys_log2
	LIBRARY DESTINATION ${PROJECT_SOURCE_DIR}/${OUTPUT_LIB}
	ARCHIVE DESTINATION ${PROJECT_SOURCE_DIR}/${OUTPUT_LIB})
install(FILES ${PROJECT_SOURCE_DIR}/sys_log/include/sys_log.h DESTINATION ${PROJECT_SOURCE_DIR}/${OUTPUT_LIB}/include)
