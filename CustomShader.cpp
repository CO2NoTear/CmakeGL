//
//  CustomShader.cpp
//  GLTEST
//
//  Created by 孙权恩 on 2023/9/7.
//

#include <CustomShader.h>
#include <stdio.h>

Shader::Shader(const char* vertexPath, const char* fragmentPath) {
  // Step1. get source code from file
  std::string vertexCode;
  std::string fragmentCode;
  std::ifstream vShaderFile;
  std::ifstream fShaderFile;
  // ensure exception
  vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  try {
    // open file
    vShaderFile.open(vertexPath);
    fShaderFile.open(fragmentPath);
    // read stream buffer
    std::stringstream vShaderStream, fShaderStream;
    vShaderStream << vShaderFile.rdbuf();
    fShaderStream << fShaderFile.rdbuf();
    // close file
    vShaderFile.close();
    fShaderFile.close();
    // stream to string
    vertexCode = vShaderStream.str();
    fragmentCode = fShaderStream.str();
  } catch (std::ifstream::failure e) {
    std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
  }
  const char* vShaderCode = vertexCode.c_str();
  const char* fShaderCode = fragmentCode.c_str();

  // Step2. compile the code
  unsigned int vertex, fragment;
  int success;
  char infoChar[512];

  // vertex shader
  vertex = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex, 1, &vShaderCode, NULL);
}
