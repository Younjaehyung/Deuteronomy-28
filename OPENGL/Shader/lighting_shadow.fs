#version 330 core
//그림자 추가제외하고는 기본 lighing과 같음
out vec4 fragColor;
const int MAX_lights = 20;

in VS_OUT {
    vec3 fragPos;
    vec3 normal;
    vec2 texCoord;
    vec4 fragPosLight[MAX_lights];
} fs_in;


struct Light {
    int directional;    //속성ID값 spot인지 direction인지

    vec3 position;
    vec3 direction;
    vec2 cutoff;
    vec3 attenuation;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};


uniform Light lights[MAX_lights]; // UBO로부터 여러 라이트 정보


uniform vec3 viewPos;
uniform int blinn;
uniform sampler2D shadowMaps[MAX_lights];    //쉐도우 맵
uniform int numLights;  // 활성화된 라이트 수

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
    float bias = max(0.02 * (1.0 - dot(normal, lightDir)), 0.001);

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
 vec3 result = vec3(0.0);
    vec3 texColor = texture(material.diffuse, fs_in.texCoord).rgb;


    // 기본 색상 (예: 빨강)으로 설정하여 텍스처 로딩 문제 확인
   
    vec3 ambientLight = vec3(0.05,0.035,0.0) * texColor; 
    result += ambientLight;

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
    //result = vec3(result.x/numLights,result.y/numLights,result.z/numLights);
    //fragColor = vec4(texture(shadowMaps[0], fragCoord.xy).rrr, 1.0);
    float alpha = texture(material.diffuse, fs_in.texCoord).a;
    if(alpha <0.01)
        discard;

    fragColor = vec4(result,alpha );
}
