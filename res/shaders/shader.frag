#version 330 core

out vec4 FragColor;

uniform float RED;
uniform float GREEN;
uniform float BLUE;
void main()
{
    FragColor = vec4(RED,GREEN,BLUE, 1.0f);
}
