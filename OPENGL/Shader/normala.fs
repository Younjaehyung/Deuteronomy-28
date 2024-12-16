#version 330 core
in vec3 normal;     //표면의 벡터
in vec2 texCoord;   //텍스쳐 좌표
in vec3 position;   //픽셀의 위치
out vec4 fragColor;

uniform vec3 viewPos;   //보고있는 위치(시점)


struct Material {
    sampler2D diffuse;   //텍스쳐,   재질의 주변광 색상  //재질의 확산광 색상(물체의 기본색)
    sampler2D specular; //재질의 반사광 색상
    float shininess;    // 반사광의 강도 (표면의 광택도)
};
uniform Material material;




void main() {
    //텍스쳐를 가져와서 해당 픽셀의 색상을 계산함
    vec4 texColor = texture(material.diffuse, texCoord);
 
    if (texColor.a < 0.01)
        discard;

    fragColor = texColor * 0.4;
}