#ifndef GLM_TEST
#define GLM_TEST
#include <glad/glad.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

#include "CustomShader.h"
#include "utils.h"

int main() {
  GLFWwindow* window = initWindow(800, 600);

  glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
  glm::mat4 trans = glm::mat4(1.0f);
  // move vec by (1.0, 1.0, 0)
  trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 0.0f));
  vec = trans * vec;
  std::cout << vec.x << vec.y << vec.z << std::endl;

  glm::mat4 rotation_trans = glm::mat4(1.0f);
  // rotate on z-axis (0,0,1)
  rotation_trans = glm::rotate(rotation_trans, glm::radians(90.0f),
                               glm::vec3(0.0, 0.0, 1.0));
  rotation_trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));

  while (!glfwWindowShouldClose(window)) {
    processInput(window);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  return 0;
}
#endif