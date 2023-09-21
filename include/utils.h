#pragma once
#include <glad/glad.h>

#include <GLFW/glfw3.h>

#include <iostream>

#include "LearnGLConfig.h"

GLFWwindow *initWindow(const unsigned int SCR_WIDTH,
                       const unsigned int SCR_HEIGHT);

void processInput(GLFWwindow *window);
void framebuffer_size_callback(GLFWwindow *window, int width, int height);
std::string JoinProjectAbsolutePath(std::string);