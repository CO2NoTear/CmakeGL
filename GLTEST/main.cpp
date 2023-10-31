#include <glad/glad.h>

#include <GLFW/glfw3.h>

#include <iostream>

#include "CustomShader.h"
#include "LearnGLConfig.h"
#include "glm/gtc/type_ptr.hpp"
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
  GLFWwindow *window = initWindow(SCR_WIDTH, SCR_HEIGHT);
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
  Shader shader(vertexShaderSource, fragmentShaderSource);

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
  float vertices[] = {// position			//color
                      -0.5,-0.5,-0.5, 0.5,-0.5,-0.5, 0.5,0.5,-0.5, -0.5,0.5,-0.5,
 -0.5,-0.5,0.5, 0.5,-0.5,0.5, 0.5,0.5,0.5, -0.5,0.5,0.5,
 0.0,0.0,0.0, 1.0,0.0,0.0, 1.0,1.0,0.0, 0.0,1.0,0.0,
 0.0,0.0,1.0, 1.0,0.0,1.0, 1.0,1.0,1.0, 0.0,1.0,1.0};
  unsigned int indices[] = {0, 1, 2, 1, 3, 4};
  unsigned int indices2[] = {
3, 1, 2,
1, 0, 3,
3, 6, 2,
3, 7, 6,
7, 0, 4,
7, 3, 0,
6, 5, 1,
2, 1, 6,
5, 6, 7,
4, 5, 7,
4, 0, 1,
5, 1, 4,
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

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices2), indices2,
               GL_STATIC_DRAW);

  //    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
  //    (void*)0);
  // position
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  // it enables location at 0 to apply the attributes
  glEnableVertexAttribArray(0);
  // color
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
                        (void *)(24 * sizeof(float)));
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

  glm::mat4 perspective =
      glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
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
  shader.use();
  shader.setMat4("view", view);
  shader.setMat4("projection", perspective);


  glEnable(GL_DEPTH_TEST);
  while (!glfwWindowShouldClose(window)) {
    // input
    // -----
    processInput(window);
    std::cout<<cameraPos.x<<cameraPos.y<<cameraPos.z<<std::endl;
    view = camera->updateView();
    shader.setMat4("view", view);


    // render
    // ------
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // draw our first triangle
    // glUseProgram(shaderProgram);
    shader.use();
    glBindVertexArray(VAO);    // seeing as we only have a single VAO there's no
                               // need to bind it every time, but we'll do so to
                               // keep things a bit more organized
    // glDrawArrays(GL_TRIANGLES, 0, 6);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
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
