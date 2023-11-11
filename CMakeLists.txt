cmake_minimum_required(VERSION 3.20)
project(LearnGL VERSION 1.0)

message("PROJECT_BINARY_DIR = ${PROJECT_BINARY_DIR}")
message("PROJECT_SOURCE_DIR = ${PROJECT_SOURCE_DIR}")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    # Windows平台的配置
	set(GLFW_PATH "D:/OpenGL")
	set(GLFW_INCLUDE_PATH "${GLFW_PATH}/include")
	set(GLAD_PATH "D:/OpenGL")
	set(GLAD_INCLUDE_PATH "${GLAD_PATH}/include")
	set(ASSIMP_PATH "D:/OpenGL")
	set(ASSIMP_INCLUDE_PATH "${ASSIMP_PATH}/include")
	find_package(OpenGL REQUIRED)
	LINK_LIBRARIES("D:/OpenGL/lib/glfw3.lib")
	LINK_LIBRARIES("D:/OpenGL/lib/assimpd.lib")

	LINK_LIBRARIES("opengl32.lib")

elseif (APPLE)
    # macOS平台的配置
	set(GLFW_PATH "/opt/homebrew/Cellar/glfw/3.3.8")
	set(GLFW_INCLUDE_PATH "${GLFW_PATH}/include")
	set(GLAD_PATH "/Users/co2notear/Dependencies/glad")
	set(GLAD_INCLUDE_PATH "${GLAD_PATH}/include")
	set(ASSIMP_PATH "/Users/co2notear/Dependencies/assimp")
	set(ASSIMP_INCLUDE_PATH "${ASSIMP_PATH}/include")
	find_package(glfw3 3.3 REQUIRED)
	find_package(OpenGL REQUIRED)
	LINK_LIBRARIES("${GLFW_PATH}/lib/libglfw.dylib")
	link_libraries("-framework Cocoa -framework OpenGL -framework IOKit")
	LINK_LIBRARIES("${ASSIMP_PATH}/bin/libassimp.5.3.0.dylib")

elseif (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    # Linux平台的配置
endif()

configure_file(LearnGLConfig.h.in LearnGLConfig.h)

# library
# link_directories("${GLFW_PATH}/lib/")
add_subdirectory(glad_dependency)
LINK_LIBRARIES(GLAD)
# 格式： add_executable(PROJECT_NAME, [Source...])
add_executable(MyAnswer
	"${PROJECT_SOURCE_DIR}/GLTEST/main.cpp"
	# "${PROJECT_SOURCE_DIR}/GLTEST/GLMTest.cpp"
	# "${PROJECT_SOURCE_DIR}/GLTEST/Light.cpp"
	# "${PROJECT_SOURCE_DIR}/glad_dependency/glad.c"
	"${PROJECT_SOURCE_DIR}/include/CustomShader.cpp"
	"${PROJECT_SOURCE_DIR}/include/utils.cpp"
	# "${PROJECT_SOURCE_DIR}/GLTEST/texture.cpp"
	)
add_executable(CameraProj
	# "${PROJECT_SOURCE_DIR}/glad_dependency/glad.c"
	"${PROJECT_SOURCE_DIR}/GLTEST/CoordsSys.cpp"
	"${PROJECT_SOURCE_DIR}/include/CustomShader.cpp"
	"${PROJECT_SOURCE_DIR}/include/utils.cpp"
	)
add_executable(ExerciseAnswer
	"${PROJECT_SOURCE_DIR}/include/CustomShader.cpp"
	"${PROJECT_SOURCE_DIR}/include/utils.cpp"
	# "${PROJECT_SOURCE_DIR}/glad_dependency/glad.c"
	# "${PROJECT_SOURCE_DIR}/Exercise Answers/TextureTransform.cpp"
	"${PROJECT_SOURCE_DIR}/Exercise Answers/DrawALine.cpp"
)
if(APPLE)
	# target_link_libraries(MyAnswer PUBLIC "-framework Cocoa -framework OpenGL -framework IOKit")
	# target_link_libraries(ExerciseAnswer PUBLIC "-framework Cocoa -framework OpenGL -framework IOKit")
	# target_link_libraries(CameraProj PUBLIC "-framework Cocoa -framework OpenGL -framework IOKit")
endif()
# include path (Recommended to add at the end of Cmakelist)
target_include_directories(MyAnswer PUBLIC
	"${PROJECT_SOURCE_DIR}"
	"${PROJECT_SOURCE_DIR}/include/"
	"${GLAD_INCLUDE_PATH}"
	"${GLFW_INCLUDE_PATH}"
	"${ASSIMP_INCLUDE_PATH}"
	)
target_include_directories(CameraProj PUBLIC
	"${PROJECT_SOURCE_DIR}"
	"${PROJECT_SOURCE_DIR}/include/"
	"${GLAD_INCLUDE_PATH}"
	"${GLFW_INCLUDE_PATH}"
	"${ASSIMP_INCLUDE_PATH}"
	)
target_include_directories(ExerciseAnswer PUBLIC
	"${PROJECT_SOURCE_DIR}"
	"${PROJECT_SOURCE_DIR}/include/"
	"${GLAD_INCLUDE_PATH}"
	"${GLFW_INCLUDE_PATH}"
	"${ASSIMP_INCLUDE_PATH}"
	)
