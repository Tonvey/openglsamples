// shader版本
#version 120
//属性，这个属性用来获取定点位置，具体的顶点值，由C++传值
attribute vec3 vertexPosition;
attribute vec2 coord;
varying vec2 vertex_coord;

//shader主程序
void main()
{
    //gl_Position 是最终输出的位置，使用了其次坐标
    vertex_coord = coord;
    gl_Position = vec4 ( vertexPosition,1.0);
}
