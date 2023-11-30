#include <glad/glad.h>

#include <GLFW/glfw3.h>

#include <cmath>
#include <cstddef>
#include <glm/glm.hpp>
#include <iostream>
#include <random>
#include <vector>

#include "CustomShader.h"
#include "build/LearnGLConfig.h"
#include "utils.h"

void processMouseInput(GLFWwindow *window);
long long comb[20][20];
typedef vector<glm::vec3> Vertices;
Vertices control_vertices = {
    glm::vec3(0.1f, 0.1f, 0.0f),
};
Vertices control_vertices_auto = {
    glm::vec3(0.1f, 0.1f, 0.0f),
};
static default_random_engine eng;
static uniform_real_distribution<float> dis(-0.0001, 0.0001);
static std::vector<uniform_real_distribution<float>> randfloat;

long long get_comb(int m, int n) {
  if (comb[m][n]) return comb[m][n];
  if (comb[n - m][n]) return comb[m][n] = comb[n - m][n];
  long long frac = 1;
  for (long long i = 1; i <= m; ++i) {
    frac *= i + m;
    frac /= i;
  }
  return comb[m][n] = frac;
}

float *bezier(Vertices control_vertices, size_t precision, glm::vec3 color) {
  float **vertices = new float *[precision];
  for (int i = 0; i < precision; ++i) {
    vertices[i] = new float[3];
    vertices[i][0] = 0;
    vertices[i][1] = 0;
    vertices[i][2] = 0;
  }

  unsigned int n = control_vertices.size();

  float u = 0;
  for (size_t it = 0; it < precision; ++it) {
    for (size_t m = 0; m < n; ++m) {
      float B = get_comb(m, n - 1) * pow(u, m) * pow((1 - u), n - 1 - m);
      vertices[it][0] += B * control_vertices[m].x;
      vertices[it][1] += B * control_vertices[m].y;
      vertices[it][2] += B * control_vertices[m].z;
    }
    u += 1.0 / precision;
  }

  float *result = new float[precision * 6];
  for (size_t i = 0; i < precision; ++i) {
    // position
    result[i * 6] = vertices[i][0];
    result[i * 6 + 1] = vertices[i][1];
    result[i * 6 + 2] = vertices[i][2];
    delete[] vertices[i];
    // color: RED
    result[i * 6 + 3] = color.x;
    result[i * 6 + 4] = color.y;
    result[i * 6 + 5] = color.z;
    // delete[] vertices[i];
  }
  // delete[] vertices;
  return result;
}
float *bres(unsigned int x0, unsigned int y0, unsigned int xe,
            unsigned int ye) {
  int xs, ys;  // starting point
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
  // std::cout << "C[2][4] is " << get_comb(2, 4) << std::endl;
  GLFWwindow *window = initWindow(800, 600);
  // glfwSetCursorPosCallback(window, mouse_callback);
  unsigned int VBO[4], VAO[4];
  glad_glGenVertexArrays(4, VAO);
  glGenBuffers(4, VBO);
  // float vertices[] = {-0.5f, -0.5f, 0.0f, 0.8f, 0.0f,  0.0f,  0.5f, 0.5f,
  //                     0.0f,  0.0f,  0.8f, 0.0f, -0.3f, -0.5f, 0.0f, 0.8f,
  //                     0.8f,  0.0f,  0.3f, 0.5f, 0.0f,  0.8f,  0.8f, 0.8f};

  // float *vertices = bres(50, 275, 650, 325);
  std::string shaderPath = PROJECT_SOURCE_DIR;
  Shader shaderProgram(
      (shaderPath + std::string("/Exercise Answers/") + "line.vs").c_str(),
      (shaderPath + std::string("/Exercise Answers/") + "line.fs").c_str());

  glm::mat4 ortho = glm::ortho(0.0f, 1.0f, 0.0f, 1.0f, -0.1f, 1.0f);
  shaderProgram.use();
  shaderProgram.setMat4("projection", ortho);
  float rand_range = dis(eng);
  randfloat.push_back(uniform_real_distribution<float>(-0.002 + rand_range,
                                                       0.002 + rand_range));
  while (!glfwWindowShouldClose(window)) {
    processMouseInput(window);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

    glClearColor(0.2f, 0.3f, 0.2f, 0.0f);
    glPointSize(10.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    unsigned int precision = 5000;
    float *control_points_manual = new float[6 * control_vertices.size()];
    for (size_t i = 0; i < control_vertices.size(); ++i) {
      control_points_manual[i * 6 + 0] = control_vertices[i].x;
      control_points_manual[i * 6 + 1] = control_vertices[i].y;
      control_points_manual[i * 6 + 2] = control_vertices[i].z;
      // BLUE
      control_points_manual[i * 6 + 3] = 0.0f;
      control_points_manual[i * 6 + 4] = 0.0f;
      control_points_manual[i * 6 + 5] = 1.0f;
    }
    float *control_points_auto = new float[6 * control_vertices.size()];
    for (size_t i = 0; i < control_vertices_auto.size(); ++i) {
      control_vertices_auto[i].x += randfloat[i](eng);
      control_vertices_auto[i].y += randfloat[i](eng);
      control_vertices_auto[i].z += randfloat[i](eng);
      control_points_auto[i * 6 + 0] = control_vertices_auto[i].x;
      control_points_auto[i * 6 + 1] = control_vertices_auto[i].y;
      control_points_auto[i * 6 + 2] = control_vertices_auto[i].z;
      // GREEN
      control_points_auto[i * 6 + 3] = 0.0f;
      control_points_auto[i * 6 + 4] = 1.0f;
      control_points_auto[i * 6 + 5] = 0.0f;
    }

    // MANUAL
    float *vertices =
        bezier(control_vertices, precision, glm::vec3(1.0f, 0.0f, 0.0f));
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBindVertexArray(VAO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * precision, vertices,
                 GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                          (void *)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                          (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBindVertexArray(VAO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * control_vertices.size(),
                 control_points_manual, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                          (void *)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                          (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(VAO[0]);
    glDrawArrays(GL_POINTS, 0, precision);

    glBindVertexArray(VAO[1]);
    glDrawArrays(GL_POINTS, 0, control_vertices.size());
    // std::cout << glad_glGetError() << std::endl;
    // AUTO
    float *vertices_auto =
        bezier(control_vertices_auto, precision, glm::vec3(0.0f, 0.5f, 0.5f));
    glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);
    glBindVertexArray(VAO[2]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * precision, vertices_auto,
                 GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                          (void *)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                          (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, VBO[3]);
    glBindVertexArray(VAO[3]);
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(float) * 6 * control_vertices_auto.size(),
                 control_points_auto, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                          (void *)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                          (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(VAO[2]);
    glDrawArrays(GL_POINTS, 0, precision);

    glBindVertexArray(VAO[3]);
    glDrawArrays(GL_POINTS, 0, control_vertices_auto.size());

    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  return 0;
}
void processMouseInput(GLFWwindow *window) {
  static float lastTime = 0.0f;
  float currentTime = glfwGetTime();
  float deltaTime = currentTime - lastTime;
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
  if (deltaTime > 0.5f && glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1)) {
    lastTime = currentTime;
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    control_vertices.push_back(glm::vec3(xpos / 800, (1 - ypos / 600), 0.0f));
    control_vertices_auto.push_back(
        glm::vec3(xpos / 800, (1 - ypos / 600), 0.0f));
    float rand_range = dis(eng);
    randfloat.push_back(uniform_real_distribution<float>(-0.002 + rand_range,
                                                         0.002 + rand_range));
  }
}