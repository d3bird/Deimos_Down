#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec3 ourColor;
out vec2 TexCoord;
out float state;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform float m_state;

uniform vec2 resolution;
uniform float u_time;


void main()
{
	float x = aPos.x;
	float y = aPos.y;

	float amplitude = 1.;
	float frequency = 1.;

	y = sin(x * frequency);
	float t = 0.01*(-1*130.0);
	y += sin(x*frequency*2.1 + t)*4.5;
	y += sin(x*frequency*1.72 + t*1.121)*4.0;
	y += sin(x*frequency*2.221 + t*0.437)*5.0;
	y += sin(x*frequency*3.1122+ t*4.269)*2.5;
	y *= amplitude*0.06;

	gl_Position = vec4(aPos, 1.0);
	//gl_Position = projection * view * model * vec4(aPos, 1.0f);
	//gl_Position = projection * view  * vec4(aPos, 1.0f);
	ourColor = aColor;
	TexCoord = vec2(aTexCoord.x, aTexCoord.y);
	state = m_state;


}