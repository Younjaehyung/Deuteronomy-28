#version 330

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in ivec4 boneIds;
layout (location = 4) in vec4 weights;

out VS_OUT {
  vec3 fragPos;	//프레그먼트 포지션의 위치
  vec3 normal;
  vec2 texCoord;
  vec4 fragPosLight;	//빛을 기준으로 했을때 픽셀 위치
} vs_out;

const int MAX_BONES = 200;
const int MAX_BONE_INFLUENCE = 4;
//uniform mat4 finalBonesMatrices[MAX_BONES];

layout (std140) uniform Bones { mat4 finalBonesMatrices[MAX_BONES]; };


uniform mat4 transform;
uniform mat4 modelTransform;
uniform mat4 lightTransform;


void main()
{
	vec4 totalPosition = vec4(0.f);
	for(int i = 0; i < MAX_BONE_INFLUENCE; i++)
	{
		if(boneIds[i] == -1)
			continue;
		if(boneIds[i] >= MAX_BONES)
		{
			totalPosition = vec4(aPos, 1.0);
			break;
		}
		vec4 localPosition = finalBonesMatrices[boneIds[i]] * vec4(aPos, 1.0);
		totalPosition += localPosition * weights[i];
	}
	gl_Position = transform * totalPosition;


	vs_out.fragPos = vec3(modelTransform * vec4(aPos, 1.0));
	vs_out.normal = transpose(inverse(mat3(modelTransform))) * aNormal;
	vs_out.texCoord = aTexCoord;
	vs_out.fragPosLight = lightTransform * vec4(vs_out.fragPos, 1.0);
}