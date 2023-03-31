#version 330 core

out vec4 myOutputColor;
uniform float RESOLUTION;
void main() {
    vec2 pos = gl_FragCoord.xy/(RESOLUTION);
    myOutputColor = vec4(pos.x, pos.y,0.0,1.0);
}
