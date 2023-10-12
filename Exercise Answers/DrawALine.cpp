#include <glad/glad.h>

#include <GLFW/glfw3.h>

#include "CustomShader.h"
#include "LearnGLConfig.h"
#include "utils.h"

float *bres(unsigned int x0, unsigned int y0, unsigned int xe,
            unsigned int ye) {
  int xs, ys;    // starting point
  unsigned int delta_x, delta_y;
  if (x0 < xe) {
    xs = x0;
    ys = y0;
    delta_x = xe - x0;
    delta_y = ye - y0;
  } else {
    xs = xe;
    ys = ye;
    delta_x = x0 - xe;
    delta_y = y0 - ye;
  }
  int p = 2 * delta_y - delta_x;
  float **vertices = new float *[delta_x];
  for (int i = 0; i < delta_x; ++i) {
    vertices[i] = new float[3];
  }
  vertices[0][0] = x0;
  vertices[0][1] = y0;
  vertices[0][2] = 0;
  for (int i = 1; i < delta_x; ++i) {
    vertices[i][0] = vertices[i - 1][0] + 1;
    vertices[i][1] = vertices[i - 1][1];
    vertices[i][2] = 0;
    if (p > 0) {
      p -= 2 * delta_x;
      vertices[i][1] += 1;
    }
    p += 2 * delta_y;
  }
  float *result = new float[delta_x * 3];
  for (int i = 0; i < delta_x; ++i) {
    result[i * 3] = vertices[i][0];
    result[i * 3 + 1] = vertices[i][1];
    result[i * 3 + 2] = vertices[i][2];
    delete[] vertices[i];
  }
  delete[] vertices;
  return result;
}

int main() {
  GLFWwindow *window = initWindow(800, 600);
  unsigned int VBO, VAO;
  glad_glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  // float vertices[] = {-0.5f, -0.5f, 0.0f, 0.8f, 0.0f,  0.0f,  0.5f, 0.5f,
  //                     0.0f,  0.0f,  0.8f, 0.0f, -0.3f, -0.5f, 0.0f, 0.8f,
  //                     0.8f,  0.0f,  0.3f, 0.5f, 0.0f,  0.8f,  0.8f, 0.8f};

  float *vertices = bres(50, 275, 650, 325);
  glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * (650 - 50), vertices,
               GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);
  // glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
  //                       (void *)(3 * sizeof(float)));
  // glEnableVertexAttribArray(1);

  std::string shaderPath = PROJECT_SOURCE_DIR;
  Shader shaderProgram(
      (shaderPath + std::string("/Exercise Answers/") + "line.vs").c_str(),
      (shaderPath + std::string("/GLTEST/") + "shader.fs").c_str());

  glm::mat4 ortho = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, -0.1f, 100.0f);
  shaderProgram.use();
  shaderProgram.setMat4("projection", ortho);
  while (!glfwWindowShouldClose(window)) {
    processInput(window);

    glClearColor(0.2f, 0.3f, 0.2f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glBindVertexArray(VAO);

    glDrawArrays(GL_POINTS, 0, 600);
    std::cout << glad_glGetError() << std::endl;

    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  return 0;
}