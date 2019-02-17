#version 330
layout(location=0) in vec3 vertexPosition;
//layout(location=1) in vec2 uv;
uniform mat4 mvp;
void main()
{
    //uvCoord = uv;
    gl_Position = mvp * vec4 (vertexPosition,1.0) ;
}
