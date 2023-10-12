if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    # Windows平台的配置
	set(GLFW_PATH "D:\\OpenGL\\glfw-3.3.8")
	set(GLFW_INCLUDE_PATH "${GLFW_PATH}/include")
	set(GLAD_PATH "D:\\OpenGL")
	set(GLAD_INCLUDE_PATH "${GLAD_PATH}/include")
elseif (CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    # macOS平台的配置
	set(GLFW_PATH "/opt/homebrew/Cellar/glfw/3.3.8/")
	set(GLFW_INCLUDE_PATH "${GLFW_PATH}/include")
	set(GLAD_PATH "/Users/co2notear/Dependencies/glad/")
	set(GLAD_INCLUDE_PATH "${GLAD_PATH}/include")
	find_package(glfw3 3.3 REQUIRED)
	find_package(OpenGL REQUIRED)
elseif (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    # Linux平台的配置
endif()
add_library(GLAD SHARED glad.c)
target_include_directories(GLAD
	PUBLIC
	"${GLAD_INCLUDE_PATH}")
