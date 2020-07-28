//shader 版本
#version 120

//shader主程序
varying vec3 vertex_color;
void main()
{
    //最终输出颜色，为红色
    gl_FragColor = vec4(vertex_color,1);
}
