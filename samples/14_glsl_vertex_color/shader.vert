// shader版本
#version 120
//属性，这个属性用来获取定点位置，具体的顶点值，由C++传值
attribute vec3 vertexPosition_modelspace;
attribute vec3 vertexColor_modelspace;
varying vec3 vertex_color;

//shader主程序
void main()
{
    //gl_Position 是最终输出的位置，使用了其次坐标
    vertex_color = vertexColor_modelspace;
    gl_Position = vec4 ( vertexPosition_modelspace,1.0);
}
