#version 330 core
in vec2 bPos;
out vec4 fragColor;
//https://www.shadertoy.com/view/tscBWl
uniform float numbOfRows;
uniform float numbOfColumns;
void main()
{
    //5.0 number of colums times 2
    fragColor = vec4(max(sign(fract((bPos.x+1)*numbOfColumns)-0.5) * sign(fract((bPos.y+1)*numbOfRows)-0.5),0.0));
}
