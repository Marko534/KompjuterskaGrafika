#version 330 core
out vec4 FragColor;
in vec3 aColor;
void main()
{
    FragColor = vec4(aColor, 1.0f);
}
