cmake_minimum_required(VERSION 3.20)
project(LearnGL VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(GLFW_PATH "/opt/homebrew/Cellar/glfw/3.3.8/")
set(GLFW_INCLUDE_PATH "${GLFW_PATH}/include")
set(GLAD_PATH "/Users/co2notear/Dependencies/glad/")
set(GLAD_INCLUDE_PATH "${GLAD_PATH}/include")

configure_file(LearnGLConfig.h.in LearnGLConfig.h)

# library
add_subdirectory(glad_dependency)
# 格式： add_executable(PROJECT_NAME, [Source...])
add_executable(MyAnswer
	# "${PROJECT_SOURCE_DIR}/GLTEST/main.cpp"
	# "${PROJECT_SOURCE_DIR}/GLTEST/GLMTest.cpp"
	"${PROJECT_SOURCE_DIR}/GLTEST/CoordsSys.cpp"
	"${PROJECT_SOURCE_DIR}/include/CustomShader.cpp"
	"${PROJECT_SOURCE_DIR}/include/utils.cpp"
	# "${PROJECT_SOURCE_DIR}/GLTEST/texture.cpp"
	)
add_executable(ExerciseAnswer
	"${PROJECT_SOURCE_DIR}/include/CustomShader.cpp"
	"${PROJECT_SOURCE_DIR}/include/utils.cpp"
	"${PROJECT_SOURCE_DIR}/Exercise Answers/TextureTransform.cpp"
	# "${PROJECT_SOURCE_DIR}/Exercise Answers/DrawALine.cpp"
)

find_package(glfw3 3.3 REQUIRED)
find_package(OpenGL REQUIRED)

# target_link_libraries(LearnGL PUBLIC glfw -framework Cocoa -framework OpenGL -framework IOKit)
target_link_libraries(MyAnswer PUBLIC glfw GLAD)
target_link_libraries(ExerciseAnswer PUBLIC glfw GLAD)

# include path (Recommended to add at the end of Cmakelist)
target_include_directories(MyAnswer PUBLIC
	"${PROJECT_SOURCE_DIR}"
	"${PROJECT_SOURCE_DIR}/include/"
	"${GLAD_INCLUDE_PATH}"
	"${GLFW_INCLUDE_PATH}"
	)
target_include_directories(ExerciseAnswer PUBLIC
	"${PROJECT_SOURCE_DIR}"
	"${PROJECT_SOURCE_DIR}/include/"
	"${GLAD_INCLUDE_PATH}"
	"${GLFW_INCLUDE_PATH}"
	)
message("PROJECT_BINARY_DIR = ${PROJECT_BINARY_DIR}")
message("PROJECT_SOURCE_DIR = ${PROJECT_SOURCE_DIR}")
