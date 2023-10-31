project(glad_dependency)
set(GLAD_PATH "D:/OpenGL")
set(GLAD_INCLUDE_PATH "${GLAD_PATH}/include")
add_library(GLAD glad.c)
message("${PROJECT_SOURCE_DIR}")
target_include_directories(GLAD
	PUBLIC
	"${GLAD_INCLUDE_PATH}")
