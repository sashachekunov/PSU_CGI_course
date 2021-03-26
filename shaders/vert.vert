#version 330 core

// Input vertex data, different for all executions of this shader.
in vec2 vertex;

void main(){
    // gl_line
    gl_Position = vec4(vertex, 0, 1);
}