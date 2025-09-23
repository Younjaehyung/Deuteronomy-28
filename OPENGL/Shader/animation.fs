#version 330 core

out vec4 fragColor;
const int MAX_lights = 20;

in VS_OUT {
    vec3 fragPos;
    vec3 normal;
    vec2 texCoord;
    vec4 fragPosLight[MAX_lights]; // 각 라이트의 관점에서의 좌표
} fs_in;

struct Light {
    int directional;    // 0: 포인트/스포트라이트, 1: 방향광
    vec3 position;
    vec3 direction;
    vec2 cutoff;        // 스포트라이트용 cutoff angles
    vec3 attenuation;   // (const, linear, quadratic)
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
uniform Light lights[MAX_lights]; // UBO로부터 여러 라이트 정보


uniform vec3 viewPos;   // 시점 위치
uniform sampler2D shadowMaps[MAX_lights]; // 여러 쉐도우맵을 위한 배열
uniform int numLights;  // 활성화된 라이트 수
uniform int blinn;

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};
uniform Material material;



float ShadowCalculation(vec4 fragPosLight, sampler2D shadowMap, vec3 normal, vec3 lightDir) {
    vec3 projCoords = fragPosLight.xyz / fragPosLight.w;
    projCoords = projCoords * 0.5 + 0.5; // [0, 1] 범위로 변환

    //if (projCoords.z > 1.0) return 0.0; // 빛의 사각형 밖

    float closestDepth = texture(shadowMap, projCoords.xy).r;
    float currentDepth = projCoords.z;
    float bias = max(0.02 * (1.0 - dot(normal, lightDir)), 0.005);

    float shadow = 0.0;
    vec2 texelSize = 1.0 / textureSize(shadowMap, 0);
    for (int x = -1; x <= 1; ++x) {
        for (int y = -1; y <= 1; ++y) {
            float pcfDepth = texture(shadowMap, projCoords.xy + vec2(x, y) * texelSize).r;
            shadow += currentDepth - bias > pcfDepth ? 1.0 : 0.0;
        }
    }
    shadow /= 9.0;
    return shadow;
}

void main() {
    vec3 texColor = texture(material.diffuse, fs_in.texCoord).rgb;
    vec3 result = vec3(0.0);

    for (int i = 0; i < numLights; ++i) {
        Light light = lights[i];
        vec3 ambient = texColor * light.ambient;

        vec3 lightDir;
        float attenuation = 1.0;
        float intensity = 1.0;

        if (light.directional == 1) {
            lightDir = normalize(-light.direction);
        } else {
            float dist = length(light.position - fs_in.fragPos);
            vec3 distPoly = vec3(1.0, dist, dist * dist);
            attenuation = 1.0 / dot(distPoly, light.attenuation);
            lightDir = (light.position - fs_in.fragPos) / dist;

            //if (light.cutoff[0] > 0.0) {
                float theta = dot(lightDir, normalize(-light.direction));
                intensity = clamp((theta - light.cutoff[1]) / (light.cutoff[0] - light.cutoff[1]), 0.0, 1.0);
           // }
        }

        if (intensity > 0.0) {
            vec3 pixelNorm = normalize(fs_in.normal);
            float diff = max(dot(pixelNorm, lightDir), 0.0);
            vec3 diffuse = diff * texColor * light.diffuse;

            vec3 specColor = texture(material.specular, fs_in.texCoord).rgb;
            float spec = 0.0;

            vec3 viewDir = normalize(viewPos - fs_in.fragPos);
            if (blinn == 0) {
                vec3 reflectDir = reflect(-lightDir, pixelNorm);
                spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
            } else {
                vec3 halfDir = normalize(lightDir + viewDir);
                spec = pow(max(dot(halfDir, pixelNorm), 0.0), material.shininess);
            }
            vec3 specular = spec * specColor * light.specular;

            float shadow = ShadowCalculation(fs_in.fragPosLight[i], shadowMaps[i], pixelNorm, lightDir);
            result += (ambient + (diffuse + specular) * intensity * (1.0 - shadow)) * attenuation;
        }
    }

    fragColor = vec4(result * 8.0f, 1.0);
}
