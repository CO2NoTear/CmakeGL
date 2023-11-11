project(glad_dependency)
if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    # Windows平台的配置
	set(GLAD_PATH "D:/OpenGL")
	set(GLAD_INCLUDE_PATH "${GLAD_PATH}/include")
add_library(GLAD glad.c)

elseif (CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    # macOS平台的配置
	set(GLAD_PATH "/Users/co2notear/Dependencies/glad/")
	set(GLAD_INCLUDE_PATH "${GLAD_PATH}/include")
	add_library(GLAD SHARED glad.c)
elseif (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    # Linux平台的配置
endif()
message("${PROJECT_SOURCE_DIR}")
target_include_directories(GLAD
	PUBLIC
	"${GLAD_INCLUDE_PATH}")
