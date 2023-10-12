#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
out vec4 vertexColor;
uniform mat4 projection;
void main()
{
   gl_Position = projection * vec4(aPos, 1.0f);
   vertexColor = vec4(0.8f, 0.0f, 0.0f, 1.0f);
}
