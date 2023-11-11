#include <glad/glad.h>

#include "utils.h"

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

#include "CustomShader.h"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/quaternion_trigonometric.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

glm::mat4 Camera::updateView() {
  view_ = glm::lookAt(cameraPos_, cameraPos_ + cameraFront_, cameraUp_);
  return view_;
}
void Camera::setSpeed(const float val) { cameraSpeed_ = val; }
void Camera::setFov(const float val) { fov = val; }
const float Camera::getFov() { return fov; }
const glm::vec3 Camera::getPos() { return cameraPos_; }
void Camera::move(GLFWwindow *window) {
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

  float currentTime = glfwGetTime();
  deltaTime = currentTime - lastTime;
  lastTime = currentTime;
  float cameraSpeed = cameraSpeed_ * deltaTime;
  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    cameraPos_ += cameraSpeed * cameraFront_;
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    cameraPos_ -= cameraSpeed * cameraFront_;
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    cameraPos_ -=
        glm::normalize(glm::cross(cameraFront_, cameraUp_)) * cameraSpeed;
  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    cameraPos_ +=
        glm::normalize(glm::cross(cameraFront_, cameraUp_)) * cameraSpeed;
  if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    cameraPos_ += cameraSpeed * cameraUp_;
  if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
    cameraPos_ -= cameraSpeed * cameraUp_;
}
void Camera::mouse(float xoffset, float yoffset) {
  yaw += xoffset;
  pitch += yoffset;

  if (pitch > 89.0f) pitch = 89.0f;
  if (pitch < -89.0f) pitch = -89.0f;

  glm::vec3 front;
  front.y = sin(glm::radians(pitch));
  front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
  front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
  cameraFront_ = glm::normalize(front);
}
Camera::Camera(glm::vec3 cameraPos, glm::vec3 cameraFront, glm::vec3 cameraUp)
  : cameraPos_(cameraPos), cameraFront_(cameraFront), cameraUp_(cameraUp) {
  cameraSpeed_ = 50.0f;
}
Camera::Camera() {}

Camera *camera = new Camera();

GLFWwindow *initWindow(const unsigned int SCR_WIDTH,
                       const unsigned int SCR_HEIGHT) {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

  // glfw window creation
  // --------------------
  GLFWwindow *window =
      glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
  if (window == NULL) {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return NULL;
  }
  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
  glfwSetCursorPosCallback(window, mouse_callback);
  glfwSetScrollCallback(window, scroll_callback);

  // glad: load all OpenGL function pointers
  // ---------------------------------------
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return NULL;
  }
  return window;
}

// process all input: query GLFW whether relevant keys are pressed/released this
// frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInputWithoutMoving(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
}
void processInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
  if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
    camera->perspective =
        glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, -1.0f, 20.0f);
  if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
    camera->perspective =
        glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
  camera->move(window);
}
// void processInput(GLFWwindow *window, Camera *camera) {
//   if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//     glfwSetWindowShouldClose(window, true);
//   camera->move(window);
// }

// glfw: whenever the window size changed (by OS or user resize) this callback
// function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  // make sure the viewport matches the new window dimensions; note that width
  // and height will be significantly larger than specified on retina displays.
  glViewport(0, 0, width, height);
}
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
  if (camera->getFov() >= 1.0f && camera->getFov() <= 45.0f)
    camera->setFov(camera->getFov() - yoffset);
  if (camera->getFov() <= 1.0f) camera->setFov(1.0f);
  if (camera->getFov() >= 45.0f) camera->setFov(45.0f);
}
void mouse_callback(GLFWwindow *window, double xpos, double ypos) {
  static float lastX = 400, lastY = 300;
  // std::cout << "x = " << xpos << "; y = " << ypos << std::endl;
  float xoffset = xpos - lastX;
  float yoffset = lastY - ypos;
  lastX = xpos;
  lastY = ypos;
  float sensitivity = 0.05f;
  xoffset *= sensitivity;
  yoffset *= sensitivity;

  camera->mouse(xoffset, yoffset);
}

std::string JoinProjectAbsolutePath(std::string src) {
  if (*(src.begin()) != '/') {
    src = '/' + src;
  }
  if (*(src.end() - 1) != '/') {
    src = src + '/';
  }
  return std::string(PROJECT_SOURCE_DIR) + src;
}
void Model::Draw(Shader &shader) {
  for (unsigned int i = 0; i < meshes.size(); i++) meshes[i].Draw(shader);
}

unsigned int TextureFromFile(const char *path, const string &directory) {
  string filename = string(path);
  filename = directory + '/' + filename;

  unsigned int textureID;
  glGenTextures(1, &textureID);

  int width, height, nrComponents;
  unsigned char *data =
      stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
  if (data) {
    GLenum format;
    if (nrComponents == 1)
      format = GL_RED;
    else if (nrComponents == 3)
      format = GL_RGB;
    else if (nrComponents == 4)
      format = GL_RGBA;

    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format,
                 GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                    GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_image_free(data);
  } else {
    std::cout << "Texture failed to load at path: " << path << std::endl;
    stbi_image_free(data);
  }

  return textureID;
}