#shader vertex
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 vertColor;
out vec4 fragColor;

uniform mat4 mViewProj;

void main()
{
	fragColor = vec4(vertColor, 1.0);
	gl_Position = mViewProj * vec4(position, 1.0);
};


#shader fragment
#version 330 core

in vec4 fragColor;
out vec4 color;

void main()
{
	color = fragColor;
};

