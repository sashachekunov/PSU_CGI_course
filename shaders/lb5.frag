#version 330

in float len;
out vec3 FragColor;

void main()
{
    FragColor = vec3(2.0f, 2.0f, 2.0f)/len;
}
