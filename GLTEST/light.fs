#version 330 core
out vec4 FragColor;
in vec3 Normal;
in vec3 FragPos;
uniform vec3 lightPos;
uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 viewPos;

void main()
{
    // ambient lighting
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    // normalization reduces the computation wightload
    vec3 norm = normalize(Normal);
    float specularStrength = 0.5;
    vec3 lightDir = normalize(lightPos - FragPos);
    // specular lighting
    vec3 viewDir = normalize(viewPos - FragPos);
    // utility function: reflect(dirFromLightToFrag, normal)
    vec3 reflectDir = reflect(-lightDir, norm);
    // 32 is how specular is the surface 
    float spec = pow(max(0.0, dot(viewDir, reflectDir)), 64);
    // specular lighting is basically considering
    // how much source light can be seen by the viewer
    vec3 specular = specularStrength * spec * lightColor;

    // diffuse lighting
    // compute the angle (negative for no light, so 0 is set)
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;


    vec3 result = (ambient + diffuse + specular) * objectColor;
    FragColor = vec4(result, 1.0);
}