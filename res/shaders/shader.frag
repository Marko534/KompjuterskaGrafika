#version 330 core

void main() {
    vec2 pos = gl_Position.xy;
    gl_FragColor = vec4(pos.x,pos.y,0.0,1.0);
}
