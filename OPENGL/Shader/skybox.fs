#version 330 core
out vec4 fragColor;
in vec3 texCoord;

uniform samplerCube skybox; //큐브 박스를 이용하기 위해 samplerCube 자료형 사용

void main() {
    fragColor = texture(skybox, texCoord);
}