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

        
    //vec2 st = gl_FragCoord.xy / resolution.xy;
    //float glitch = random(st * time);
    //if (glitch > 0.9) {
    //    st.x += random(st) * 0.9; // X축 글리치
    //    pixel.xyz += random(st) * vec3(0.4, 0.8, 0.9); // 색상 왜곡
    //}

    vec2 st = gl_FragCoord.xy / resolution.xy;
    float noise = random(st * time); // 랜덤 노이즈
    float scanline = sin(st.y * resolution.y * 0.1 + time * 50.0) * 0.1; // 스캔 라인

    //vec3 color = texture(screenTexture, st).rgb;
     pixel.xyz += vec3(noise + scanline) * 0.2; // 노이즈와 스캔 라인 결합
    //gl_FragColor = vec4( pixel.xyz, 1.0);

    fragColor = pixel;
}