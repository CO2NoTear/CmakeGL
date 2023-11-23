project(glad_dependency)
if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
	set(GLAD_PATH "D:/OpenGL")
elseif (CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    # macOS平台的配置
	set(GLAD_PATH "/Users/co2notear/Dependencies/glad/")
	endif()
set(GLAD_INCLUDE_PATH "${GLAD_PATH}/include")
add_library(GLAD glad.c)
message("${PROJECT_SOURCE_DIR}")
target_include_directories(GLAD
	PUBLIC
	"${GLAD_INCLUDE_PATH}")
