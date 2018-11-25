#version 430 core
#extension GL_EXT_texture_array : enable

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 uvs;

uniform mat4 M;

out vec2 uv;

void main()
{
	uv = uvs;
	gl_Position =  M * vec4(position ,1.0) ;
}
