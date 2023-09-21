#version 330 core
out vec4 FragColor;
in vec3 ourColor;
in vec2 TexCoord;
// sampler2D is a built-in variable
uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
//  texture(sampler, coordinates) is a built-in function
//  that outputs the sampled color for texcoords.
    FragColor = mix(texture(texture1, TexCoord), texture(texture2, 
TexCoord), 0.2);
}