#version 330 core
layout (location = 0) in vec3 aPos;
out vec2 bPos;
//ZOSTO TREBA DA NAPRAJME ourColor = aColor a ne samo da out vec3 aColor
void main()
{
    bPos=vec2(aPos.xy);
    gl_Position = vec4(aPos, 1.0);
}
