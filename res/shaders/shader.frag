#version 330 core

out vec4 FragColor;
in vec3 bCol;

void main()
{
        // linearly interpolate between both textures (80% container, 20% awesomeface)
        FragColor = vec4(bCol, 1.0f);
}
