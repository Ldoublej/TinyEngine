#version 430 core
#extension GL_EXT_texture_array : enable

uniform sampler2DArray mainTex;

in vec2 uv;

void main()
{
	gl_FragColor = texture2DArray(mainTex, vec3(uv,0));
}
