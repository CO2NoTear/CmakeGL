#version 330 core
struct Material {
    vec3 ambient;
    vec3 diffuse;
    // uniform sampler2D;
    vec3 specular;
    float shininess;
}; 
struct Light {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

out vec4 FragColor;
in vec3 Normal;
in vec3 FragPos;
uniform vec3 lightPos;
// uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 viewPos;
uniform Material material;
uniform Light light;
uniform bool blinn;

void main()
{
    // ambient lighting
    // float ambientStrength = 0.1;
    vec3 ambient = material.ambient * light.ambient;

    // normalization reduces the computation wightload
    vec3 norm = normalize(Normal);
    // float specularStrength = 0.5;
    vec3 lightDir = normalize(lightPos - FragPos);
    // specular lighting
    vec3 viewDir = normalize(viewPos - FragPos);
    // utility function: reflect(dirFromLightToFrag, normal)
    // vec3 reflectDir = reflect(-lightDir, norm);
    // 32 is how specular is the surface 
    float spec;
    if(blinn)
    {
        vec3 halfwayDir = normalize(lightDir + viewDir);  
        spec = pow(max(dot(norm, halfwayDir), 0.0), 16.0);
    }
    else
    {
        vec3 reflectDir = reflect(-lightDir, norm);
        spec = pow(max(dot(viewDir, reflectDir), 0.0), 8.0);
    }
    // specular lighting is basically considering
    // how much source light can be seen by the viewer
    vec3 specular = light.specular * (material.specular * spec);

    // diffuse lighting
    // compute the angle (negative for no light, so 0 is set)
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * (diff * material.diffuse);


    vec3 result = (ambient + diffuse + specular); 
    FragColor = vec4(result, 0.6);
}