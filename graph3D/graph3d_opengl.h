#ifndef GRAPH3D_OPENGL_H
#define GRAPH3D_OPENGL_H

#include <QGLWidget>
//#include <QWindow>
#include <QOpenGLContext>
#include <QOpenGLShaderProgram>
#include <QOpenGLShader>
#include <QOpenGLBuffer>
#include <QTimer>
#include <QMouseEvent>

#include "graph3D/graph3d.h"

class Graph3D_OpenGL : public QGLWidget//, protected QOpenGLFunctions
//class Graph3D_OpenGL : public QWindow//, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    Graph3D_OpenGL();
    //Graph3D_OpenGL(QScreen *screen = 0);
    ~Graph3D_OpenGL();
    //QOpenGLFunctions_4_3_Core* m_funcs;


//protected slots:
    void resizeGL();
    void initializeGL();
    void prepareShaderProgram();
    void prepareVertexBuffers();
    void setGeometry();
    void paintGL();


protected:
    void hideEvent(QHideEvent *event);

    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent (QMouseEvent * event);
    void mouseMoveEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent * event );
    bool event(QEvent *event);
    virtual void keyPressEvent(QKeyEvent *event);
    virtual void timerEvent(QTimerEvent *event);

    void AutoRotate();

public:
    void axis3D();
    void updateBackGroundColor(const QColor &color);

protected:
    QOpenGLContext m_context;
    QOpenGLShaderProgram m_shaderProgram;
    QOpenGLBuffer m_vertexPositionBuffer;
    QOpenGLBuffer m_vertexColorBuffer;
    //QOpenGLBuffer m_projectionBuffer;
    //QOpenGLBuffer m_orientationBuffer;
    QTimer *timer;
    QMatrix4x4 projection;
    QMatrix4x4 orientation;


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
