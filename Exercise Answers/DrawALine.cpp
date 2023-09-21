#include <glad/glad.h>

#include <GLFW/glfw3.h>

#include "CustomShader.h"
#include "LearnGLConfig.h"
#include "utils.h"

int main() {
  GLFWwindow *window = initWindow(800, 600);
  unsigned int VBO, VAO;
  glad_glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  float vertices[] = {-0.5f, -0.5f, 0.0f, 0.8f, 0.0f,  0.0f,  0.5f, 0.5f,
                      0.0f,  0.0f,  0.8f, 0.0f, -0.3f, -0.5f, 0.0f, 0.8f,
                      0.8f,  0.0f,  0.3f, 0.5f, 0.0f,  0.0f,  0.0f, 0.0f};
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                        (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  std::string shaderPath = PROJECT_SOURCE_DIR + std::string("/GLTEST/");
  Shader shaderProgram((shaderPath + "shader.vs").c_str(),
                       (shaderPath + "shader.fs").c_str());
  while (!glfwWindowShouldClose(window)) {
    processInput(window);

    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    shaderProgram.use();
    glBindVertexArray(VAO);
    glDrawArrays(GL_LINES, 0, 4);
    // std::cout << glad_glGetError() << std::endl;

    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  return 0;
}