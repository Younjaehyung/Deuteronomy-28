#version 330 core

out vec4 fragColor;

in vec3 normal;
in vec3 position;

uniform vec3 cameraPos;
uniform samplerCube skybox;

void main() {
    vec3 I = normalize(position - cameraPos);   //물체를 바라보는 벡터
    vec3 R = reflect(I, normalize(normal)); //물체로부터 반사된 벡터
    fragColor = vec4(texture(skybox, R).rgb, 1.0);  //반사된 벡터가 벡터와 만나는 곳의 색상을 가져온다.
}