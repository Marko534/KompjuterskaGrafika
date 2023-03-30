#version 330 core
in vec3 ourColor;
//out vec4 FragColor;
uniform int RESOLUTION;
void main()
{
    vec2 st = gl_Position.xy/RESOLUTION;
    gl_FragColor = vec4(st.x,0.0f, 0.0f, 0.0f );
}
