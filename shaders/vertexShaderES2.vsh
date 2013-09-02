//#version 130
uniform mediump mat4 matrix;
uniform mediump mat4 proj;

attribute vec4 vertexPosition;
attribute vec4 VertexColor;

varying vec4 Color;

void main(void)
{
    Color = VertexColor;
    gl_Position = proj*matrix * vertexPosition;
    //gl_Position = vertexPosition;
}
