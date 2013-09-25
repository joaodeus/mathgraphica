#ifndef GRAPH2D_OPENGL_H
#define GRAPH2D_OPENGL_H

#include <QGLWidget>
#include <QOpenGLShaderProgram>
#include <QOpenGLContext>
#include <QOpenGLBuffer>
#include <QMouseEvent>
#include "graph2d.h"

class Graph2D_OpenGL : public QGLWidget
{
public:
    Graph2D_OpenGL(Calculator *calc_);
    ~Graph2D_OpenGL();

    void initializeGL();
    void prepareShaderProgram();
    void prepareVertexBuffers();
    void resizeGL(int width, int height);
    void showEvent(QShowEvent *event);
    void paintGL();

    void initializeAxis2D();
    void drawAxis2D();

protected:
    QOpenGLShaderProgram m_shaderProgram;
    QOpenGLBuffer m_vertexPositionBuffer;
    QOpenGLBuffer m_vertexColorBuffer;
    QOpenGLBuffer m_testeBufferPosition;
    QOpenGLBuffer m_testeBufferColor;

    GLint vertexAttr;
    GLint matrixAttr;
    GLint projAttr;
    QMatrix4x4 projection;
    QMatrix4x4 orientation;

    QColor backgroundColor;

    int w;//width
    int h;//height
    double Range;
    double scale;
    QVector3D *dots;// = new QVector3D[number_of_dots];
    QVector3D *dotsColor;// = new QVector3D[number_of_dots];
    int number_of_dots;


    // axis
    QVector3D axis2D[4];
    QVector3D axisColor[4];
    QVector3D *axis2Ddots;


    void mousePressEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent * event);
    void mouseMoveEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent * event);
    bool event(QEvent *event);

    //coordinates
    QPointF translate_xy;
    QPointF lastPos;
    QPointF MouseCoordinates_ToViewport(const QPointF &p);

    // graphs
    Graph2D m_graph2D;
public:
    QList<Graph2D> m_graph2DList;

    void addGraph2D(const Graph2D &graph2d_);

private:
    Calculator *calc;
};

#endif // GRAPH2D_OPENGL_H
