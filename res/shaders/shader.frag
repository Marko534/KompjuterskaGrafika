#version 330 core
in vec2 bPos;
out vec4 fragColor;
//https://www.shadertoy.com/view/tscBWl
void main()
{
    fragColor = vec4(fract((bPos.x+1))*5.0f);
}
