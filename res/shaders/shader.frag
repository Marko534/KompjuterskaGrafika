#version 330 core
in vec2 bPos;
out vec4 fragColor;

void main()
{
    fragColor = vec4(sign(fract(bPos.x*0.01)-0.5) * sign(fract(bPos.y*0.01)-0.5));
}
