attribute highp vec4 vertex;
uniform mediump mat4 matrix;
uniform mediump mat4 proj;

attribute highp vec4 VertexColor;
varying highp vec4 Color;

void main(void)
{
    Color = VertexColor;
    gl_Position = proj*matrix * vertex;
}
