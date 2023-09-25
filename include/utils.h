#pragma once
#include <glad/glad.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

#include "LearnGLConfig.h"

GLFWwindow *initWindow(const unsigned int SCR_WIDTH,
                       const unsigned int SCR_HEIGHT);

class Camera {
 public:
  glm::mat4 updateView() {
    view_ = glm::lookAt(cameraPos_, cameraPos_ + cameraFront_, cameraUp_);
    return view_;
  }
  void setSpeed(const float val) {
    cameraSpeed_ = val;
    return;
  }
  void move(GLFWwindow *window) {
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
  }
  void mouse(float xoffset, float yoffset) {
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
  Camera(glm::vec3 cameraPos, glm::vec3 cameraFront, glm::vec3 cameraUp)
    : cameraPos_(cameraPos), cameraFront_(cameraFront), cameraUp_(cameraUp) {
    cameraSpeed_ = 50.0f;
  }
  Camera() {}
  // Camera(const Camera &copy)
  //   : cameraPos_(copy.cameraPos_),
  //     cameraFront_(copy.cameraFront_),
  //     cameraUp_(copy.cameraUp_) {}

 private:
  glm::vec3 cameraPos_;
  glm::vec3 cameraFront_;
  glm::vec3 cameraUp_;
  glm::mat4 view_;
  float cameraSpeed_;
  float deltaTime = 0.0f;
  float lastTime = 0.0f;
  float yaw = -90.0f;
  float pitch = 0.0f;
};
extern Camera camera;
void processInput(GLFWwindow *window);
void processInput(GLFWwindow *window, Camera *camera);
void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void mouse_callback(GLFWwindow *window, double xpos, double ypos);
std::string JoinProjectAbsolutePath(std::string);