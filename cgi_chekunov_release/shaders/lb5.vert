#version 330 core

layout(location = 0) in vec3 vertexPosition_modelspace;
uniform mat4 MVP;
out float len;

void main()
{
    len = length(MVP * vec4(vertexPosition_modelspace, 1));
	gl_Position =  MVP * vec4(vertexPosition_modelspace, 1);
}
