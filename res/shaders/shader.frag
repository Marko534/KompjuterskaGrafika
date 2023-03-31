#version 330 core
out vec4 fragColor;
uniform int GRID_SIZE;
const vec4 COL_EVEN = vec4(1.0, 1.0, 1.0, 1.0);
const vec4 COL_ODD = vec4(0.0, 0.0, 0.0, 1.0);

void main()
{
    vec2 m = mod(gl_FragCoord.xy,  GRID_SIZE);
    if (m.x < GRID_SIZE && m.y < GRID_SIZE ||
    m.x >= GRID_SIZE && m.y >= GRID_SIZE)
    fragColor = COL_EVEN;
    else
    fragColor = COL_ODD;
}
