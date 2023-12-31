#include <glad/glad.h>

#include <GLFW/glfw3.h>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include <assimp/Importer.hpp>
#include <iostream>
#include <string>

#include "CustomShader.h"
#include "build/LearnGLConfig.h"
#include "glm/ext/matrix_transform.hpp"
#include "stb_image.h"
#include "utils.h"

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// const char *vertexShaderSource =
//     "#version 330 core\n"
//     "layout (location = 0) in vec3 aPos;\n"
//     "layout (location = 1) in vec3 aColor;\n"
//     "out vec4 vertexColor;\n"
//     "void main()\n"
//     "{\n"
//     "   gl_Position = vec4(aPos, 1.0f);\n"
//     "   vertexColor = vec4(aColor, 1.0f);\n"
//     "}\0";
// const char *fragmentShaderSource =
//     "#version 330 core\n"
//     "in vec4 vertexColor;\n"
//     "out vec4 FragColor;\n"
//     //	"uniform vec4 uniColor;\n"
//     "void main()\n"
//     "{\n"
//     "   FragColor = vertexColor;\n"
//     //	"   FragColor = uniColor;\n"
//     "}\n\0";

int main() {
  // glfw: initialize and configure
  // ------------------------------
  GLFWwindow *window = initCameraWindow(SCR_WIDTH, SCR_HEIGHT);
  if (!window) {
    std::cerr << "Unable to InitWindow at " << SCR_HEIGHT << "x" << SCR_WIDTH
              << std::endl;
    return -1;
  }
  // bulid shader from Shader class
  std::string shaderPath = "/";
  std::string vertexCode =
      PROJECT_SOURCE_DIR + std::string("/GLTEST/shader.vs");
  const char *vertexShaderSource = vertexCode.c_str();
  std::string fragmentCode =
      PROJECT_SOURCE_DIR + std::string("/GLTEST/shader.fs");
  const char *fragmentShaderSource = fragmentCode.c_str();
  Shader box_shader(vertexShaderSource, fragmentShaderSource);

  std::string modelVertexCode =
      PROJECT_SOURCE_DIR + std::string("/GLTEST/model_shader.vs");
  const char *modelVertexShaderSource = modelVertexCode.c_str();
  std::string modelFragmentCode =
      PROJECT_SOURCE_DIR + std::string("/GLTEST/model_shader.fs");
  const char *modelFragmentShaderSource = modelFragmentCode.c_str();
  Shader suit_shader(modelVertexShaderSource, modelFragmentShaderSource);
  glm::vec3 suit_position = glm::vec3(0.0f, 0.0f, -18.0f);
  glm::mat4 suit_model_mat = glm::mat4(1.0f);
  suit_model_mat = glm::translate(suit_model_mat, suit_position);
  suit_shader.use();
  suit_shader.setMat4("model", suit_model_mat);

  std::string skyboxVertexCode =
      PROJECT_SOURCE_DIR + std::string("/GLTEST/skybox.vs");
  const char *skyboxVertexShaderSource = skyboxVertexCode.c_str();
  std::string skyboxFragmentCode =
      PROJECT_SOURCE_DIR + std::string("/GLTEST/skybox.fs");
  const char *skyboxFragmentShaderSource = skyboxFragmentCode.c_str();
  Shader skybox_shader(skyboxVertexShaderSource, skyboxFragmentShaderSource);

  stbi_set_flip_vertically_on_load(true);
  Model ourModel(
      (std::string(PROJECT_SOURCE_DIR) + "/resource/nanosuit.obj").c_str());

  // set up vertex data (and buffer(s)) and configure vertex attributes
  // ------------------------------------------------------------------
  //    float vertices[] = {
  //         0.5f,  0.5f, 0.0f,  // top right
  //         0.5f, -0.5f, 0.0f,  // bottom right
  //        -0.5f, -0.5f, 0.0f,  // bottom left
  //        -0.5f,  0.5f, 0.0f   // top left
  //    };
  //    unsigned int indices[] = {  // note that we start from 0!
  //        0, 1, 3,  // first Triangle
  //        1, 2, 3   // second Triangle
  //    };
  // float vertices[] = {// position			//color
  //                     -0.5, -0.5, -0.5, 0.5,  -0.5, -0.5, 0.5,  0.5, -0.5,
  //                     -0.5, 0.5,  -0.5, -0.5, -0.5, 0.5,  0.5,  -0.5, 0.5,
  //                     0.5,  0.5, 0.5,  -0.5, 0.5,  0.5,  0.0,  0.0,
  //                     0.0,  1.0, 0.0,  0.0, 1.0,  1.0,  0.0,  0.0,  1.0, 0.0,
  //                     0.0,  0.0, 1.0,  1.0, 0.0,  1.0,  1.0,  1.0,  1.0, 0.0,
  //                     1.0,  1.0};
  // unsigned int indices[] = {0, 1, 2, 1, 3, 4};
  // unsigned int indices2[] = {
  //     3, 1, 2, 1, 0, 3, 3, 6, 2, 3, 7, 6, 7, 0, 4, 7, 3, 0,
  //     6, 5, 1, 2, 1, 6, 5, 6, 7, 4, 5, 7, 4, 0, 1, 5, 1, 4,
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
  glm::vec3 model_positions[] = {
      glm::vec3(0.0f, 0.0f, -9.0f),
      glm::vec3(3.0f, 0.0f, -9.0f),
      glm::vec3(-3.0f, 0.0f, -9.0f),
  };
  unsigned int VBO, VAO, EBO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);
  //     bind the Vertex Array Object first, then bind and set vertex buffer(s),
  //     and then configure vertex attributes(s).
  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices2), indices2,
  //              GL_STATIC_DRAW);

  //    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
  //    (void*)0);
  // position
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
  // it enables location at 0 to apply the attributes
  glEnableVertexAttribArray(0);
  // color
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                        (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  // note that this is allowed, the call to glVertexAttribPointer registered VBO
  // as the vertex attribute's bound vertex buffer object so afterwards we can
  // safely unbind
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  // remember: do NOT unbind the EBO while a VAO is active as the bound element
  // buffer object IS stored in the VAO; keep the EBO bound.
  // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  // You can unbind the VAO afterwards so other VAO calls won't accidentally
  // modify this VAO, but this rarely happens. Modifying other VAOs requires a
  // call to glBindVertexArray anyways so we generally don't unbind VAOs (nor
  // VBOs) when it's not directly necessary.
  glBindVertexArray(0);

  // uncomment this call to draw in wireframe polygons.
  //    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  // render loop
  // -----------
  glm::mat4 view = glm::mat4(1.0f);
  view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

  // glm::mat4 perspective = glm::perspective(
  //     glm::radians(45.0f), 1.0f * SCR_WIDTH / SCR_HEIGHT, 0.1f, 100.0f);
  glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
  glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
  // normalized vec3 for camera moving direction (opposite to the direction
  // where we are looking at)
  glm::vec3 cameraMovingDirection = glm::normalize(cameraPos = cameraTarget);
  // right direction of the camera moving direction
  // applying Schmidt Process
  glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
  glm::vec3 cameraRight =
      glm::normalize(glm::cross(worldUp, cameraMovingDirection));
  glm::vec3 cameraUp =
      glm::normalize(glm::cross(cameraMovingDirection, cameraRight));

  glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
  *camera = Camera(cameraPos, cameraFront, worldUp);
  camera->setSpeed(3.0f);
  box_shader.use();
  box_shader.setMat4("view", view);
  box_shader.setMat4("projection", camera->perspective);

  suit_shader.use();
  suit_shader.setMat4("view", view);
  suit_shader.setMat4("projection", camera->perspective);

  skybox_shader.use();
  skybox_shader.setMat4("view", view);
  skybox_shader.setMat4("projection", camera->perspective);
  skybox_shader.setInt("skybox", 0);

  glEnable(GL_DEPTH_TEST);
  // glEnable(GL_CULL_FACE);
  // glEnable(GL_BLEND);
  // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  vector<std::string> faces{
      (std::string(PROJECT_SOURCE_DIR) + "/resource/skybox/" + "right.jpg")
          .c_str(),
      (std::string(PROJECT_SOURCE_DIR) + "/resource/skybox/" + "left.jpg")
          .c_str(),
      (std::string(PROJECT_SOURCE_DIR) + "/resource/skybox/" + "top.jpg")
          .c_str(),
      (std::string(PROJECT_SOURCE_DIR) + "/resource/skybox/" + "bottom.jpg")
          .c_str(),
      (std::string(PROJECT_SOURCE_DIR) + "/resource/skybox/" + "front.jpg")
          .c_str(),
      (std::string(PROJECT_SOURCE_DIR) + "/resource/skybox/" + "back.jpg")
          .c_str()};
  unsigned int cubemapTexture = loadCubemap(faces);
  float skyboxVertices[] = {
      // positions
      -1.0f, 1.0f,  -1.0f, -1.0f, -1.0f, -1.0f, 1.0f,  -1.0f, -1.0f,
      1.0f,  -1.0f, -1.0f, 1.0f,  1.0f,  -1.0f, -1.0f, 1.0f,  -1.0f,

      -1.0f, -1.0f, 1.0f,  -1.0f, -1.0f, -1.0f, -1.0f, 1.0f,  -1.0f,
      -1.0f, 1.0f,  -1.0f, -1.0f, 1.0f,  1.0f,  -1.0f, -1.0f, 1.0f,

      1.0f,  -1.0f, -1.0f, 1.0f,  -1.0f, 1.0f,  1.0f,  1.0f,  1.0f,
      1.0f,  1.0f,  1.0f,  1.0f,  1.0f,  -1.0f, 1.0f,  -1.0f, -1.0f,

      -1.0f, -1.0f, 1.0f,  -1.0f, 1.0f,  1.0f,  1.0f,  1.0f,  1.0f,
      1.0f,  1.0f,  1.0f,  1.0f,  -1.0f, 1.0f,  -1.0f, -1.0f, 1.0f,

      -1.0f, 1.0f,  -1.0f, 1.0f,  1.0f,  -1.0f, 1.0f,  1.0f,  1.0f,
      1.0f,  1.0f,  1.0f,  -1.0f, 1.0f,  1.0f,  -1.0f, 1.0f,  -1.0f,

      -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f,  1.0f,  -1.0f, -1.0f,
      1.0f,  -1.0f, -1.0f, -1.0f, -1.0f, 1.0f,  1.0f,  -1.0f, 1.0f};
  unsigned int skyboxVBO;
  glGenBuffers(1, &skyboxVBO);
  glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
  unsigned int skyboxVAO;
  glGenVertexArrays(1, &skyboxVAO);
  glBindVertexArray(skyboxVAO);

  glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), skyboxVertices,
               GL_STATIC_DRAW);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);

  while (!glfwWindowShouldClose(window)) {
    // input
    // -----
    framebuffer_size_callback(window, SCR_WIDTH, SCR_HEIGHT);
    processCameraInput(window);
    view = camera->updateView();

    box_shader.use();
    box_shader.setVec3("cameraPos", camera->getPos());
    box_shader.setMat4("view", view);
    box_shader.setMat4("projection", camera->perspective);

    // render
    // ------
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // draw our first triangle
    // glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
    glm::mat4 model = glm::mat4(1.0f);
    for (int i = 0; i < 3; ++i) {
      model = glm::mat4(1.0f);
      model = glm::translate(model, model_positions[i]);
      float angle = 20.0f * i;
      model = glm::rotate(model, angle + (float)glfwGetTime(),
                          glm::vec3(1.0f, 0.3f, 0.5f));
      box_shader.setMat4("model", model);
      // glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
      glDrawArrays(GL_TRIANGLES, 0, 36);
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
      suit_model_mat =
          glm::rotate(suit_model_mat, 0.001f, glm::vec3(0.0f, 0.0f, 1.0f));
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
      suit_model_mat =
          glm::rotate(suit_model_mat, -0.001f, glm::vec3(0.0f, 0.0f, 1.0f));
    }
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
      suit_model_mat =
          glm::rotate(suit_model_mat, 0.001f, glm::vec3(1.0f, 0.0f, 0.0f));
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
      suit_model_mat =
          glm::rotate(suit_model_mat, -0.001f, glm::vec3(1.0f, 0.0f, 0.0f));
    }
    if (glfwGetKey(window, GLFW_KEY_EQUAL) == GLFW_PRESS) {
      suit_model_mat =
          glm::scale(suit_model_mat, glm::vec3(1.001f, 1.001f, 1.001f));
    }
    if (glfwGetKey(window, GLFW_KEY_MINUS) == GLFW_PRESS) {
      suit_model_mat = glm::scale(
          suit_model_mat, glm::vec3(1 / 1.001f, 1 / 1.001f, 1 / 1.001f));
    }
    suit_shader.use();
    suit_shader.setVec3("cameraPos", camera->getPos());
    suit_shader.setMat4("model", suit_model_mat);
    suit_shader.setMat4("view", view);
    suit_shader.setMat4("projection", camera->perspective);
    ourModel.Draw(suit_shader);

    // glDepthMask(GL_FALSE);
    glDepthFunc(GL_LEQUAL);
    skybox_shader.use();
    // ... 设置观察和投影矩阵
    skybox_shader.setMat4("view", glm::mat4(glm::mat3(view)));
    // skybox_shader.setMat4("projection", camera->perspective);
    glBindVertexArray(skyboxVAO);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    // std::cerr << glad_glGetError() << std::endl;
    // glDepthMask(GL_TRUE);
    glDepthFunc(GL_LESS);
    // ... 绘制剩下的场景
    // glBindVertexArray(0); // no need to unbind it every time

    // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved
    // etc.)
    // -------------------------------------------------------------------------------
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  // optional: de-allocate all resources once they've outlived their purpose:
  // ------------------------------------------------------------------------
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteBuffers(1, &EBO);

  // glfw: terminate, clearing all previously allocated GLFW resources.
  // ------------------------------------------------------------------
  glfwTerminate();
  return 0;
}
