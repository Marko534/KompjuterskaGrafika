#version 330 core
in vec2 bPos;
out vec4 fragColor;
//https://www.shadertoy.com/view/tscBWl
uniform float numbOfRows;
uniform float numbOfColumns;
void main()
{
    //+1: all values are from 0 to 2
    //farc: gets us the value after the dot, (from 0.0 to 1.0)
    //numbOf*: changes the frec of the values
    //-0.5 gets us the value (-0.5, 0.5)
    //sign gets us -0.0 if neg 1.0 if pos
    //max(FORMULA, 0.0) when we get a neg val we need it to be 0.0 not -1.0 so we can use max for that
    fragColor = vec4(max(sign(fract((bPos.x+1)*numbOfColumns)-0.5) * sign(fract((bPos.y+1)*numbOfRows)-0.5),0.0));
}
