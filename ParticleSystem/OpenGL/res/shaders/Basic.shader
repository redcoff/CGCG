#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
uniform mat4 mViewProj;

void main()
{
	gl_Position = mViewProj * position;
};


#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

void main()
{
	color = vec4(gl_FragCoord.x / 640.0, 0.5, 0.2, 1.6);
};
