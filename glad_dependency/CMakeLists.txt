add_library(GLAD SHARED glad.c)
set(GLAD_PATH "/Users/co2notear/Dependencies/glad/")
set(GLAD_INCLUDE_PATH "${GLAD_PATH}/include")
target_include_directories(GLAD
	PUBLIC
	"${GLAD_INCLUDE_PATH}")
