#version 330 core
in vec4 vertexColor;
in vec2 texCoord;
out vec4 fragColor;

uniform sampler2D tex;

uniform vec2 resolution; // 화면 크기 (예: 1920x1080)
uniform float time;      // 시간 값 (초 단위)


float random(vec2 st) {
    return fract(sin(dot(st.xy, vec2(12.9898, 78.233))) * 43758.5453123);
}

void main() {
    vec4 pixel = texture(tex, texCoord);
    if (pixel.a < 0.01)
        discard;

        
     vec2 uv = texCoord;
    
    // 화면 흔들림 효과
    uv.x += sin(uv.y * 5.0 + time) * 0.0025; // 주기와 강도 조절
    uv.y += cos(uv.x * 5.0 + time) * 0.0025; // 주기와 강도 조절
    
    // 컬러 채널 왜곡
    float r = texture(tex, uv + vec2(0.003, 0.0)).r;
    float g = texture(tex, uv).g;
    float b = texture(tex, uv - vec2(0.003, 0.0)).b;

    // 노이즈 적용
    float noise = random(uv + time) * 0.05;
    
    fragColor = vec4(r + noise, g + noise, b + noise, 1.0);

}