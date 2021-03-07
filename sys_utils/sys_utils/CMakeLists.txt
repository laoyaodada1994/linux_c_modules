set(OUTPUT_LIB "output/lib")

include_directories(
    ${PROJECT_SOURCE_DIR}/sys_utils/include
)

aux_source_directory(${PROJECT_SOURCE_DIR}/sys_utils/ SYS_LOG_SRCS)

add_library(sys_utils SHARED ${SYS_LOG_SRCS})
add_library(sys_utils2 STATIC ${SYS_LOG_SRCS})
set_target_properties(sys_utils2 PROPERTIES OUTPUT_NAME "sys_utils")
set_target_properties (sys_utils PROPERTIES VERSION 1.4 SOVERSION 1)

set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build/sys_utils/)

install(TARGETS sys_utils sys_utils2
	LIBRARY DESTINATION ${PROJECT_SOURCE_DIR}/${OUTPUT_LIB}
	ARCHIVE DESTINATION ${PROJECT_SOURCE_DIR}/${OUTPUT_LIB})
install(FILES ${PROJECT_SOURCE_DIR}/sys_utils/include/sys_utils.h DESTINATION ${PROJECT_SOURCE_DIR}/${OUTPUT_LIB}/include)
