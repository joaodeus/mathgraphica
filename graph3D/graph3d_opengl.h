#ifndef GRAPH3D_OPENGL_H
#define GRAPH3D_OPENGL_H

//#include <QGLWidget>
#include <QWindow>
//#include <QOpenGLFunctions>
#include <QOpenGLContext>
#include <QOpenGLShaderProgram>
#include <QOpenGLShader>
#include <QOpenGLBuffer>
#include <QTimer>

#include "graph3D/graph3d.h"
//#include <QOpenGLFunctions_4_3_Core>

//class Graph3D_OpenGL : public QGLWidget//, protected QOpenGLFunctions
class Graph3D_OpenGL : public QWindow//, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    //Graph3D_OpenGL();
    Graph3D_OpenGL(QScreen *screen = 0);
    ~Graph3D_OpenGL();
    //QOpenGLFunctions_4_3_Core* m_funcs;


protected slots:
    void resizeGl();
    void initializeGl();
    void prepareShaderProgram();
    void prepareVertexBuffers();
    void setGeometry();
    void paintGl();


protected:
    void hideEvent(QHideEvent *event);

public:
    void axis3D(QOpenGLShaderProgram &m_sampleProgram, const GLint &vertexAttr, const GLint &colorAttr);
    void updateBackGroundColor(const QColor &color);

protected:
    QOpenGLContext m_context;
    QOpenGLShaderProgram m_shaderProgram;
    QOpenGLBuffer m_vertexPositionBuffer;
    QOpenGLBuffer m_vertexColorBuffer;
    QTimer *timer;
    //QMatrix4x4 projection;
    //QMatrix4x4 orientation;


    //----3D axis
    QVector3D axis_3D[6];
    QVector3D axisColor[6];
    void setup_Axis3D();



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
