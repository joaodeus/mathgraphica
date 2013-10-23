#ifndef GRAPH_H
#define GRAPH_H

#include <QOpenGLShaderProgram>

class Graph
{
public:
  //  Graph();

    virtual void draw(QOpenGLShaderProgram &m_shaderProgram) = 0;

};

#endif // GRAPH_H
