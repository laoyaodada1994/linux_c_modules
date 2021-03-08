set(OUTPUT_LIB "output/lib")

include_directories(
    ${PROJECT_SOURCE_DIR}/serial/include
)

aux_source_directory(${PROJECT_SOURCE_DIR}/serial/ SYS_LOG_SRCS)

add_library(serial SHARED ${SYS_LOG_SRCS})
add_library(serial2 STATIC ${SYS_LOG_SRCS})
set_target_properties(serial2 PROPERTIES OUTPUT_NAME "serial")
set_target_properties (serial PROPERTIES VERSION 1.4 SOVERSION 1)

set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build/serial/)

install(TARGETS serial serial2
	LIBRARY DESTINATION ${PROJECT_SOURCE_DIR}/${OUTPUT_LIB}
	ARCHIVE DESTINATION ${PROJECT_SOURCE_DIR}/${OUTPUT_LIB})
install(FILES ${PROJECT_SOURCE_DIR}/serial/include/serial.h DESTINATION ${PROJECT_SOURCE_DIR}/${OUTPUT_LIB}/include)
