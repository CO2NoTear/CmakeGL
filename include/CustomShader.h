//
//  Header.h
//  GLTEST
//
//  Created by 孙权恩 on 2023/9/7.
//

#ifndef Shader_h
#define Shader_h

#include<glad/glad.h>
#include<iostream>
#include<fstream>
#include<sstream>
#include<string>

class Shader {
	
public:
	unsigned int ID;
	Shader(const char* vertexPath, const char* fragmentPath);
	void use();
	void setInt(const std::string &name, int value) const;
	void setBool(const std::string &name, bool value) const;
	void setFloat(const std::string &name, float value) const;
};

#endif /* Header_h */
