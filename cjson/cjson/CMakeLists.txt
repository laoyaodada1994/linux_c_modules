set(OUTPUT_LIB "output/lib")

include_directories(
    ${PROJECT_SOURCE_DIR}/cjson/include
)

aux_source_directory(${PROJECT_SOURCE_DIR}/cjson/ SYS_LOG_SRCS)

add_library(cjson SHARED ${SYS_LOG_SRCS})
add_library(cjson2 STATIC ${SYS_LOG_SRCS})
set_target_properties(cjson2 PROPERTIES OUTPUT_NAME "cjson")
set_target_properties (cjson PROPERTIES VERSION 1.4 SOVERSION 1)
target_link_libraries(cjson m)

set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build/cjson/)

install(TARGETS cjson cjson2
	LIBRARY DESTINATION ${PROJECT_SOURCE_DIR}/${OUTPUT_LIB}
	ARCHIVE DESTINATION ${PROJECT_SOURCE_DIR}/${OUTPUT_LIB})
install(FILES ${PROJECT_SOURCE_DIR}/cjson/include/cJSON.h DESTINATION ${PROJECT_SOURCE_DIR}/${OUTPUT_LIB}/include)
