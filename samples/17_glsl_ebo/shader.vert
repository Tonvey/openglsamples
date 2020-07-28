#version 330
//属性，这个属性用来获取定点位置，具体的顶点值，由C++传值
layout(location=0) in vec3 vertexPosition;
//shader主程序
void main()
{
    gl_Position = vec4 (vertexPosition,1.0);
}
