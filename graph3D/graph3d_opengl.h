#ifndef GRAPH3D_OPENGL_H
#define GRAPH3D_OPENGL_H

#include <QGLWidget>
#include <QWindow>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLShader>
#include <QOpenGLBuffer>

#include "graph3D/graph3d.h"
//#include <QOpenGLFunctions_4_3_Core>

class Graph3D_OpenGL : public QGLWidget, protected QOpenGLFunctions
//class Graph3D_OpenGL : public QWindow, protected QOpenGLFunctions
{
public:
    Graph3D_OpenGL();
    //Graph3D_OpenGL(QScreen *screen = 0);

    //QOpenGLFunctions_4_3_Core* m_funcs;

    void resizeGL(int width_, int height_);
    void initializeGL();
    void paintGL();
    void axis3D(QOpenGLShaderProgram &m_sampleProgram, const GLint &vertexAttr, const GLint &colorAttr);
    void updateBackGroundColor(const QColor &color);

protected:
    QOpenGLShaderProgram m_shaderProgram;
    QOpenGLShader *m_vertexShader;
    QOpenGLShader *m_fragmentShader;
    QOpenGLBuffer *m_vertexArrayBuffer;
    QOpenGLBuffer *m_colorArrayBuffer;

    /*
    QGLShaderProgram m_shaderProgram;
    QGLShader *m_vertexShader;
    QGLShader *m_fragmentShader;
    QGLBuffer m_vertexBuffer;
    */
    //QOpenGLContext *m_context;

    //Graph3D m_graph3D;
    QList<Graph3D> m_graph3D_list;

    QColor backgroundColor;
    int w; //width
    int h; //height
    double Range;


    QPoint lastPos;
    double scale;
    double xRot;
    double yRot;
    double zRot;
    double AutoRotx;
    double AutoRoty;
    double AutoRotz;

    int TimerRotate;
    int Timer3D;

    double t; //time
    double t_delta;//time interval

    bool bAutoRotate;
    bool bTimer3D;

};

#endif // GRAPH3D_OPENGL_H
