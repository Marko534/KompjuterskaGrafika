#version 330 core
out vec4 FragColor;
in vec3 bPos;

void main()
{
        // linearly interpolate between both textures (80% container, 20% awesomeface)
        FragColor = vec4(bPos, 1.0f);
}
