#version 130
uniform mediump mat4 matrix;
uniform mediump mat4 proj;

attribute vec4 vertexPosition;
uniform vec4 vertexColor;

varying mediump vec4 Color;

void main(void)
{
    Color = vertexColor;
    gl_Position = proj*matrix * vertexPosition;
}
