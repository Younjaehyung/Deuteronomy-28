#version 330 core
const int MAX_LIGHTS = 20;

struct Light {
    int type;              // 조명 유형
    vec3 position;         // 위치 (점광, 스포트라이트용)
    vec3 direction;        // 방향 (스포트라이트, 방향광용)

    vec3 ambient; 
    vec3 diffuse;
    vec3 specular;

    float cutoff;          // 스포트라이트 내부 각도
    float outerCutoff;     // 스포트라이트 외부 각도
    vec3 attenuation;      // 감쇠 계수 (점광, 스포트라이트용)
};

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

out vec4 FragColor;
uniform vec3 color;
uniform vec3 viewPos;
uniform int numLights;
layout (std140) uniform Lights {
    Light lights[MAX_LIGHTS]; // 최대 10개의 조명
};
uniform Material material;


void main() {
    vec3 ambient = vec3(0.0);
    vec3 diffuse = vec3(0.0);
    vec3 specular = vec3(0.0);
    
    vec3 texColor = texture(material.diffuse, TexCoords).rgb;
    
    for (int i = 0; i < numLights; ++i) {
        vec3 lightDir;
        float attenuation = 1.0; //1.0
        
        if (lights[i].type == 2) { // Point Light
            float dist = length(lights[i].position - FragPos);
            attenuation = 1.0 / dot(lights[i].attenuation, vec3(1.0, dist, dist * dist));
            lightDir = normalize(lights[i].position - FragPos);
        } else if (lights[i].type == 3) { // Spot Light
            lightDir = normalize(lights[i].position - FragPos);
            float theta = dot(lightDir, normalize(-lights[i].direction));
            float epsilon = lights[i].cutoff-lights[i].outerCutoff;
            float intensity = clamp((theta - lights[i].outerCutoff) / epsilon, 0.0, 1.0);
            attenuation += intensity;
        } else { // Directional Light
            lightDir = normalize(-lights[i].direction);
        }
        
        vec3 norm = normalize(Normal);
        float diff = max(dot(norm, lightDir), 0.0);
        vec3 reflectDir = reflect(-lightDir, norm);
        vec3 viewDir = normalize(viewPos - FragPos);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
        
        ambient += 0.1 * texColor;
        diffuse += 0.1 * diff * texColor;
        specular += 0.1 * spec * vec3(texture(material.specular, TexCoords));
        
        ambient *= attenuation;
        diffuse *= attenuation;
        specular *= attenuation;
    }
    //ambient = texColor;
    FragColor = vec4(ambient + diffuse + specular, 1.0);
}
