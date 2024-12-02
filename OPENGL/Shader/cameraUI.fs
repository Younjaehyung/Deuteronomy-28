#version 330 core
out vec4 fragColor;
in vec2 texCoord;

uniform sampler2D skybox; //큐브 박스를 이용하기 위해 samplerCube 자료형 사용

void main() {
   vec4 result = texture(skybox, texCoord);
    if (result.a < 0.1){
        discard;
    }
    fragColor = result;
}