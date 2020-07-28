//shader 版本
#version 120
//shader主程序
varying vec2 vertex_coord;
uniform sampler2D myTextureSampler;
void main()
{
    gl_FragColor = texture2D(myTextureSampler,vertex_coord).rgba;
}
