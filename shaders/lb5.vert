#version 330 core

layout(location = 0) in vec3 vertexPosition_modelspace;
uniform mat4 MVP;
out float len;

void main()
{
    len = length(MVP * vec4(vertexPosition_modelspace, 1));
    // len = length(vertexPosition_modelspace);
    // len = distance(vec4(0.0f, -5.0f, 0.0f, 1.0f), MVP * vec4(vertexPosition_modelspace, 1));
	gl_Position =  MVP * vec4(vertexPosition_modelspace, 1);
}
