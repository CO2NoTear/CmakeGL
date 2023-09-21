#include <glad/glad.h>

#include <GLFW/glfw3.h>

#include <iostream>

#include "CustomShader.h"
#include "LearnGLConfig.h"
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
                      -0.5f, 0.0f, 0.0f,  0.5f,  0.0f,   0.0f,  0.0f,  0.0f,
                      0.0f,  0.0f, 0.5f,  0.0f,  -0.25f, 0.5f,  0.0f,  0.0f,
                      0.0f,  0.5f, 0.25f, 0.5f,  0.0f,   0.25f, 0.25f, 0.0f,
                      0.5f,  0.0f, 0.0f,  0.25f, 0.0f,   0.25f};
  unsigned int indices[] = {0, 1, 2, 1, 3, 4};
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
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
               GL_STATIC_DRAW);

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
  while (!glfwWindowShouldClose(window)) {
    // input
    // -----
    processInput(window);

    // render
    // ------
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // draw our first triangle
    // glUseProgram(shaderProgram);
    shader.use();
    glBindVertexArray(VAO);    // seeing as we only have a single VAO there's no
                               // need to bind it every time, but we'll do so to
                               // keep things a bit more organized
    glDrawArrays(GL_TRIANGLES, 0, 6);
    // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
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
