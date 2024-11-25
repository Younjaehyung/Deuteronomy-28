#version 330 core

out vec4 fragColor;

in VS_OUT {
    vec3 fragPos;
    vec3 normal;
    vec2 texCoord;
    vec4 fragPosLight;
} fs_in;



uniform vec3 viewPos;   //보고있는 위치(시점)

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
uniform Light light;
uniform int blinn;

struct Material {
    sampler2D diffuse;   //텍스쳐,   재질의 주변광 색상  //재질의 확산광 색상(물체의 기본색)
    sampler2D specular; //재질의 반사광 색상
    float shininess;    // 반사광의 강도 (표면의 광택도)
};
uniform Material material;
uniform sampler2D shadowMap;    //쉐도우 맵

float ShadowCalculation(vec4 fragPosLight, vec3 normal, vec3 lightDir) {    //그림자 계산 함수

  vec3 projCoords = fragPosLight.xyz / fragPosLight.w;
  // transform to [0,1] range
  projCoords = projCoords * 0.5 + 0.5;
  // get closest depth value from light’s perspective (using
  // [0,1] range fragPosLight as coords)
  float closestDepth = texture(shadowMap, projCoords.xy).r;
  // get depth of current fragment from light’s perspective
  float currentDepth = projCoords.z;
  // check whether current frag pos is in shadow
  float bias = max(0.02 * (1.0 - dot(normal, lightDir)), 0.001);
  float shadow = 0.0;
  vec2 texelSize = 1.0 / textureSize(shadowMap, 0);
  for(int x = -1; x <= 1; ++x) {
          for (int y = -1; y <= 1; ++y) {
              float pcfDepth = texture(shadowMap,
                projCoords.xy + vec2(x, y) * texelSize).r;
              shadow += currentDepth - bias > pcfDepth ? 1.0 : 0.0;
          }
  }
  shadow /= 9.0;
  return shadow;

}

void main() {
    //텍스쳐를 가져와서 해당 픽셀의 색상을 계산함
    vec3 texColor = texture(material.diffuse, fs_in.texCoord).xyz;
   
    // 주변광 계산 (해당 위치의 텍스쳐 색상 * 광원의 주변광)
    vec3 ambient = texColor * light.ambient;

    vec3 lightDir;
  float intensity=1.0;
  float attenuation = 1.0;
  vec3 result = ambient;

  if (light.directional ==1){
      lightDir = normalize(-light.direction);
  }
  else{
  float dist = length(light.position - fs_in.fragPos);
  vec3 distPoly = vec3(1.0, dist, dist*dist);
  attenuation = 1.0 / dot(distPoly, light.attenuation);
  lightDir = (light.position - fs_in.fragPos) / dist;


  float theta = dot(lightDir, normalize(-light.direction));
  intensity = clamp( (theta - light.cutoff[1]) / (light.cutoff[0] - light.cutoff[1]),0.0, 1.0);
  }


  if (intensity > 0.0) {
    vec3 pixelNorm = normalize(fs_in.normal);
    float diff = max(dot(pixelNorm, lightDir), 0.0);
    vec3 diffuse = diff * texColor * light.diffuse;

    vec3 specColor = texture2D(material.specular, fs_in.texCoord).xyz;
    float spec = 0.0;
    if (blinn == 0) {
        vec3 viewDir = normalize(viewPos - fs_in.fragPos);
        vec3 reflectDir = reflect(-lightDir, pixelNorm);
        spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    }
    else {
        vec3 viewDir = normalize(viewPos - fs_in.fragPos);
        vec3 halfDir = normalize(lightDir + viewDir);
        spec = pow(max(dot(halfDir, pixelNorm), 0.0), material.shininess);
    }
    vec3 specular = spec * specColor * light.specular;
    float shadow = ShadowCalculation(fs_in.fragPosLight,pixelNorm,lightDir);   //그림자 계산

    result += (diffuse + specular) * intensity * (1.0 - shadow);
  }

  result *= attenuation;
  fragColor = vec4(result, 1.0);
}