#version 330 core
layout (location = 0) in vec3 aPos;
//layout (location = 111) in vec3 world_coord;	//월드 좌표계 좌표

uniform mat4 transform;

void main() {
    gl_Position = transform * vec4(aPos, 1.0);
}