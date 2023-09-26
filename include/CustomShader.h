//
//  Header.h
//  GLTEST
//
//  Created by 孙权恩 on 2023/9/7.
//

#ifndef Shader_h
#define Shader_h

#include <glad/glad.h>

#include <fstream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <sstream>
#include <string>

class Shader {
 public:
  unsigned int ID;
  Shader(const char *vertexPath, const char *fragmentPath);
  void use();
  void setInt(const std::string &name, int value) const;
  void setBool(const std::string &name, bool value) const;
  void setFloat(const std::string &name, float value) const;
  void setMat4(const std::string &name, glm::mat4 value) const;
  void setVec3(const std::string &name, float v1, float v2, float v3) const;
  void setVec3(const std::string &name, glm::vec3 value) const;
};

#endif /* Header_h */
