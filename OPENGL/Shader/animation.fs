#version 330 core

in vec3 FragPos; // 월드 좌표계
in vec2 TexCoord;
in vec3 FragNormal;

out vec4 FragColor;


uniform vec3 viewPos;   //보고있는 위치(시점)

struct Light {

   vec3 direction; //태양광(모든 지점에 동일한 방향의 광선/Directional Light, Spot Light)

   vec3 attenuation; //광원의 빛 감쇠 계산식(Point Light, Spot Light)

   vec2 cutoff;    //광원의 빛 범위(Spot Light)

   vec3 position;  //광원의 위치
   vec3 ambient;   //주변광의 색상
   vec3 diffuse;   //확산광의 색상
   vec3 specular;  //반사광의 색상
};
uniform Light light;

struct Material {
    sampler2D diffuse;   //텍스쳐,   재질의 주변광 색상  //재질의 확산광 색상(물체의 기본색)
    sampler2D specular; //재질의 반사광 색상
    float shininess;    // 반사광의 강도 (표면의 광택도)
};
uniform Material material;

void main() {
    //텍스쳐를 가져와서 해당 픽셀의 색상을 계산함
    vec3 texColor = texture(material.diffuse, TexCoord).xyz;
   
    // 주변광 계산 (해당 위치의 텍스쳐 색상 * 광원의 주변광)
    vec3 ambient = texColor * light.ambient;

    //Point Light   
    float dist = length(light.position - FragPos); //(광원의 거리 = 광원의 위치 - 물체의 위치)
    vec3 distPoly = vec3(1.0, dist, dist*dist); //광원과의 거리에 따른 색상 계산을 위한 벡터
    float attenuation = 1.0 / dot(distPoly, light.attenuation); //광원과의 거리에 따른 색상 계산
    vec3 lightDir = (light.position - FragPos) / dist;      // 픽셀로부터 광원을 바라보는 벡터
    // vec3 lightDir = normalize(-light.direction);   //Directional Light
    // vec3 lightDir = normalize(light.position - position);
   


    //Spot Light
    float theta = dot(lightDir, normalize(-light.direction));   //빛이 해당 지역을 비추고 있는지 내적
    float intensity = clamp((theta - light.cutoff[1]) / (light.cutoff[0] - light.cutoff[1]),0.0, 1.0);

    vec3 result = ambient;

    //빛이 해당 지역을 비추고 있으면
    if (intensity > 0.0) {

    vec3 pixelNorm = normalize(FragNormal);  //표면의 법선 벡터의 정규화
  

    float diff = max(dot(pixelNorm, lightDir), 0.0);  // 광원을 얼마나 바라보는지 (내적)
    vec3 diffuse = diff * texColor * light.diffuse;    //분산광계산

    //specular 계산
    vec3 specColor = texture(material.specular, TexCoord).xyz;
    vec3 viewDir = normalize(viewPos - FragPos);   //픽셀로부터 시점을 바라보는 벡터
    vec3 reflectDir = reflect(-lightDir, pixelNorm);    //광원으로부터 픽셀을 바라보는 벡터 와 객체표면의 벡터
    // reflect함수: R=I−2⋅(N⋅I)⋅N    (입사벡터,표면의 법선벡터)의 반사된 방향벡터를 반환함
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess); // 반사 방향과 시점 방향의 내적, 지수로 양을 정함
    vec3 specular = spec * specColor * light.specular;  //반사광계산
    // 최종 색상 계산
    // vec3 result = ambient + diffuse + specular;

    result = (ambient + diffuse + specular) * attenuation;
    }


    FragColor = vec4(result, 1.0);
}