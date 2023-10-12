#include <glad/glad.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

#include "glm/ext/matrix_clip_space.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "CustomShader.h"
#include "stb_image.h"
#include "utils.h"

// static Camera *camera;
int main() {
  unsigned int SCR_WIDTH = 800;
  unsigned int SCR_HEIGHT = 600;
  glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
  glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
  glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
  glm::mat4 perspective =
      glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
  glm::vec3 lightPos = glm::vec3(1.2f, 1.0f, 2.0f);
  glm::mat4 model = glm::mat4(1.0f);
  model = glm::translate(model, lightPos);
  model = glm::scale(model, glm::vec3(0.2f));
  *camera = Camera(cameraPos, cameraFront, worldUp);
  camera->setSpeed(3.0f);
  GLFWwindow *window = initWindow(SCR_WIDTH, SCR_HEIGHT);

  std::string shaderPath = JoinProjectAbsolutePath("GLTEST");
  Shader lampShader((shaderPath + "light.vs").c_str(),
                    (shaderPath + "lamp.fs").c_str());
  Shader lightShader((shaderPath + "light.vs").c_str(),
                     (shaderPath + "light.fs").c_str());
  lightShader.use();
  lightShader.setMat4("projection", perspective);
  lampShader.use();
  lampShader.setMat4("model", model);
  lampShader.setMat4("projection", perspective);
  // glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));
  // float vertices[] = {
  //     //     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
  //     0.5f,  0.5f,  0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,    // 右上
  //     0.5f,  -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,    // 右下
  //     -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,    // 左下
  //     -0.5f, 0.5f,  0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f     // 左上
  // };
  float vertices[] = {
      -0.5f, -0.5f, -0.5f, 0.0f,  0.0f,  -1.0f, 0.5f,  -0.5f, -0.5f,
      0.0f,  0.0f,  -1.0f, 0.5f,  0.5f,  -0.5f, 0.0f,  0.0f,  -1.0f,
      0.5f,  0.5f,  -0.5f, 0.0f,  0.0f,  -1.0f, -0.5f, 0.5f,  -0.5f,
      0.0f,  0.0f,  -1.0f, -0.5f, -0.5f, -0.5f, 0.0f,  0.0f,  -1.0f,

      -0.5f, -0.5f, 0.5f,  0.0f,  0.0f,  1.0f,  0.5f,  -0.5f, 0.5f,
      0.0f,  0.0f,  1.0f,  0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
      0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  -0.5f, 0.5f,  0.5f,
      0.0f,  0.0f,  1.0f,  -0.5f, -0.5f, 0.5f,  0.0f,  0.0f,  1.0f,

      -0.5f, 0.5f,  0.5f,  -1.0f, 0.0f,  0.0f,  -0.5f, 0.5f,  -0.5f,
      -1.0f, 0.0f,  0.0f,  -0.5f, -0.5f, -0.5f, -1.0f, 0.0f,  0.0f,
      -0.5f, -0.5f, -0.5f, -1.0f, 0.0f,  0.0f,  -0.5f, -0.5f, 0.5f,
      -1.0f, 0.0f,  0.0f,  -0.5f, 0.5f,  0.5f,  -1.0f, 0.0f,  0.0f,

      0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.5f,  0.5f,  -0.5f,
      1.0f,  0.0f,  0.0f,  0.5f,  -0.5f, -0.5f, 1.0f,  0.0f,  0.0f,
      0.5f,  -0.5f, -0.5f, 1.0f,  0.0f,  0.0f,  0.5f,  -0.5f, 0.5f,
      1.0f,  0.0f,  0.0f,  0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

      -0.5f, -0.5f, -0.5f, 0.0f,  -1.0f, 0.0f,  0.5f,  -0.5f, -0.5f,
      0.0f,  -1.0f, 0.0f,  0.5f,  -0.5f, 0.5f,  0.0f,  -1.0f, 0.0f,
      0.5f,  -0.5f, 0.5f,  0.0f,  -1.0f, 0.0f,  -0.5f, -0.5f, 0.5f,
      0.0f,  -1.0f, 0.0f,  -0.5f, -0.5f, -0.5f, 0.0f,  -1.0f, 0.0f,

      -0.5f, 0.5f,  -0.5f, 0.0f,  1.0f,  0.0f,  0.5f,  0.5f,  -0.5f,
      0.0f,  1.0f,  0.0f,  0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
      0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  -0.5f, 0.5f,  0.5f,
      0.0f,  1.0f,  0.0f,  -0.5f, 0.5f,  -0.5f, 0.0f,  1.0f,  0.0f};
  unsigned int indices[] = {
      // note that we start from 0!
      0, 1, 3,    // first Triangle
      1, 2, 3     // second Triangle
  };
  glm::vec3 cubePositions[] = {
      glm::vec3(0.0f, 0.0f, 0.0f),    glm::vec3(2.0f, 5.0f, -15.0f),
      glm::vec3(-1.5f, -2.2f, -2.5f), glm::vec3(-3.8f, -2.0f, -12.3f),
      glm::vec3(2.4f, -0.4f, -3.5f),  glm::vec3(-1.7f, 3.0f, -7.5f),
      glm::vec3(1.3f, -2.0f, -2.5f),  glm::vec3(1.5f, 2.0f, -2.5f),
      glm::vec3(1.5f, 0.2f, -1.5f),   glm::vec3(-1.3f, 1.0f, -1.5f)};
  unsigned int VBO, VAO, EBO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);
  // bind the Vertex Array Object first, then bind and set vertex buffer(s), and
  // then configure vertex attributes(s).
  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                        (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
               GL_STATIC_DRAW);

  // positions
  // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void
  // *)0);
  // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void
  // *)0); glEnableVertexAttribArray(0); colors glVertexAttribPointer(1, 3,
  // GL_FLOAT, GL_FALSE, 8 * sizeof(float),
  //                       (void *)(3 * sizeof(float)));
  // glEnableVertexAttribArray(1);
  // textures
  // glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
  //                       (void *)(6 * sizeof(float)));
  // glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
  //                       (void *)(3 * sizeof(float)));
  // glEnableVertexAttribArray(2);

  unsigned int lightVAO;
  glGenVertexArrays(1, &lightVAO);
  glBindVertexArray(lightVAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                        (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  lightShader.use();
  lightShader.setMat4("model", glm::mat4(1.0f));
  // lightShader.setVec3("objectColor", 1.0f, 0.5f, 0.31f);
  lightShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
  lightShader.setVec3("lightPos", lightPos.x, lightPos.y, lightPos.z);
  // Material settings:
  // Bronze
  // lightShader.setVec3("material.ambient", 1.0f, 0.5f, 0.31f);
  // lightShader.setVec3("material.diffuse", 1.0f, 0.5f, 0.31f);
  // lightShader.setVec3("material.specular", 0.5f, 0.5f, 0.5f);
  // lightShader.setFloat("material.shininess", 32.0f);

  // emerald
  lightShader.setVec3("material.ambient", 0.0215, 0.1745, 0.0215);
  lightShader.setVec3("material.diffuse", 0.07568, 0.61424, 0.07568);
  lightShader.setVec3("material.specular", 0.633, 0.727811, 0.633);
  lightShader.setFloat("material.shininess", 0.6f * 128);

  lightShader.setVec3("light.ambient", 0.2f, 0.2f, 0.2f);
  lightShader.setVec3("light.diffuse", 0.5f, 0.5f, 0.5f);
  lightShader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);

  glEnable(GL_DEPTH_TEST);

  // the following steps shows how the GL compute a camera coords system
  while (!glfwWindowShouldClose(window)) {
    processInput(window);

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    lightShader.use();
    glBindVertexArray(VAO);
    // perspective =
    //     glm::perspective((float)glfwGetTime(), 800.0f / 600.0f, 0.1f,
    //     100.0f);
    // glUniformMatrix4fv(projectionLocation, 1, GL_FALSE,
    //                    glm::value_ptr(perspective));

    // model = glm::mat4(1.0f);
    // model = glm::translate(model, glm::vec3(0.0f, 0.0f, -0.3f));
    // model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f),
    //                     glm::vec3(0.5f, 1.0f, 0.0f));
    // glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));

    perspective = glm::perspective(glm::radians(camera->getFov()),
                                   800.0f / 600.0f, 0.1f, 100.0f);
    glm::mat4 view = glm::mat4(1.0f);
    /*
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -12.0f));
    view = glm::rotate(view, (float)glfwGetTime(), glm::vec3(0.0f, 1.0f,
    0.0f)); view = glm::translate(view, glm::vec3(0.0f, 0.0f, 6.0f));
    */
    // float radius = 10.0f;
    // cameraPos = glm::vec3(sin(glfwGetTime()) * radius, 0.0f,
    //                       cos(glfwGetTime()) * radius);
    // view = glm::lookAt(cameraPos, cameraTarget, worldUp);
    // shaderProgram.setMat4("view", view);
    view = camera->updateView();
    lightShader.setVec3("viewPos", camera->getPos());
    lightShader.setMat4("view", view);
    lightShader.setMat4("projection", perspective);

    glm::vec3 lampColor;
    lampColor.x = sin(glfwGetTime() * 2.0f);
    lampColor.y = sin(glfwGetTime() * 0.7f);
    lampColor.z = sin(glfwGetTime() * 1.3f);

    glm::vec3 diffuseColor =
        lampColor * glm::vec3(0.5f);    // lower the influence on diffuse
    glm::vec3 ambientColor =
        lampColor * glm::vec3(0.2f);    // lower the influence on ambient

    lightShader.setVec3("light.ambient", ambientColor);
    lightShader.setVec3("light.diffuse", diffuseColor);

    lampShader.use();
    lampShader.setMat4("view", view);
    lampShader.setMat4("projection", perspective);

    glDrawArrays(GL_TRIANGLES, 0, 36);
    lightShader.use();
    glDrawArrays(GL_TRIANGLES, 0, 36);
    // std::cout << glad_glGetError() << std::endl;
    // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }
}