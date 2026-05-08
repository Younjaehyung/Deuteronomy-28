#version 330 core
in vec4 vertexColor;
in vec2 texCoord;
out vec4 fragColor;

uniform sampler2D tex;


uniform vec2 resolution; // 화면 크기 (예: 1920x1080)
uniform float time;      // 시간 값 (초 단위)
uniform int typeID;

float random(vec2 st) {
    return fract(sin(dot(st.xy, vec2(12.9898, 78.233))) * 43758.5453123);
}

void main() {
    vec4 pixel = texture(tex, texCoord);
    if (pixel.a < 0.01)
        discard;

    if(typeID==0){
    //노이즈
    //  vec2 uv = texCoord;

    //// Horizontal offset to simulate screen tearing
    //float offset = random(vec2(uv.y, time)) * 0.01;
    //uv.x += offset;

    //// Add noise effect
    //float noise = random(uv + time);
    //vec3 noisyColor = texture(tex, uv).rgb + noise * 0.5;

    //// Apply mosaic effect
    //float blockSize = 0.001;
    //uv = floor(uv / blockSize) * blockSize;

    //pixel = texture(tex, uv) * vec4(noisyColor, 1.0);


       fragColor = pixel;
        return;
    }
    if(typeID==-1){

      vec2 uv = texCoord;


    float offset = random(vec2(uv.y, time)) * 0.01;
    uv.x += offset;

    float noise = random(uv + time);
    vec3 noisyColor = texture(tex, uv).rgb + noise * 0.5;

    float blockSize = 0.001;
    uv = floor(uv / blockSize) * blockSize;

    pixel = texture(tex, uv) * vec4(noisyColor, 1.0);


       fragColor = pixel;
        return;
    }

    if(typeID ==1){
        
     vec2 uv = texCoord;
    

    uv.x += sin(uv.y * 5.0 + time) * 0.0001; 
    uv.y += cos(uv.x * 5.0 + time) * 0.0001; 
    

    float r = texture(tex, uv + vec2(0.005, 0.0)).r;
    float g = texture(tex, uv).g;
    float b = texture(tex, uv - vec2(0.005, 0.0)).b;

    float noise = random(uv + time) * 0.05;
    fragColor = vec4(r + noise, g + noise, b + noise, 1.0);
    return;
    }
    if(typeID==2){
        vec2 uv = texCoord;
    
  
        uv.x += sin(uv.y * 5.0 + time) * 0.0001; 
        uv.y += cos(uv.x * 5.0 + time) * 0.0001; 
    

        float r = texture(tex, uv + vec2(0.005, 0.0)).r;
        float g = texture(tex, uv).g;
        float b = texture(tex, uv - vec2(0.005, 0.0)).b;

        float noise = random(uv + time) * 0.05;
        pixel = vec4(r + noise, g + noise, b + noise, 1.0);

            //vec2 st = gl_FragCoord.xy / resolution.xy;
        //float glitch = random(st * time);
        //if (glitch > 0.9) {
        //    st.x += random(st) * 0.9; // X축 글리치
        //    pixel.xyz += random(st) * vec3(0.4, 0.8, 0.9); // 색상 왜곡
        //}

        vec2 st = gl_FragCoord.xy / resolution.xy;
        noise = random(st * time); 
        float scanline = sin(st.y * resolution.y * 0.1 + time * 50.0) * 0.1;

        //vec3 color = texture(screenTexture, st).rgb;
         pixel.xyz += vec3(noise + scanline) * 0.2; 
        //gl_FragColor = vec4( pixel.xyz, 1.0);

        fragColor = pixel;
        return;
    }
    

}