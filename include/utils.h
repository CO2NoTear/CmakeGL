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
  glm::mat4 updateView();
  void setSpeed(const float val);
  void setFov(const float val);
  const float getFov();
  const glm::vec3 getPos();
  void move(GLFWwindow *window);
  void mouse(float xoffset, float yoffset);
  Camera(glm::vec3 cameraPos, glm::vec3 cameraFront, glm::vec3 cameraUp);
  Camera();
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
  float fov = 45.0f;
};
extern Camera *camera;
void processInput(GLFWwindow *window);
void processInput(GLFWwindow *window, Camera *camera);
void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void mouse_callback(GLFWwindow *window, double xpos, double ypos);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
std::string JoinProjectAbsolutePath(std::string);