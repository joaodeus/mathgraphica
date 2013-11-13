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
#include <QTime>

#include "graph3D/graph3d.h"

class Graph3D_OpenGL : public QGLWidget//, protected QOpenGLFunctions
//class Graph3D_OpenGL : public QWindow//, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    Graph3D_OpenGL();
    //Graph3D_OpenGL(QScreen *screen = 0);
    ~Graph3D_OpenGL();


    // Events
//protected slots:
    void initializeGL();
    void prepareShaderProgram();
    void prepareVertexBuffers();
    void prepareGraphs();
    void resizeGL(int width, int height);
    void showEvent(QShowEvent *event);
    void paintGL();

protected:
    void hideEvent(QHideEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent (QMouseEvent * event);
    void mouseMoveEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent * event );
    bool event(QEvent *event);
    virtual void timerEvent(QTimerEvent *event);
public:
    virtual void keyPressEvent(QKeyEvent *event);
    bool areTimeGraphs();
    void startStopTimer3D();
    void stopTimer3D();

    void setAutoRotation(const bool &autoRotation_);
    bool getAutoRotation();

public:
    // background color
    void setBackGroundColor(const QColor &color_);
private:
    QColor backgroundColor;

public:
    void SaveImageAs();

protected:
    GLint vertexAttr;
    GLint matrixAttr;
    GLint projAttr;
    QMatrix4x4 projection;
    QMatrix4x4 orientation;

    void AutoRotate();

    //----3D axis
public:
    void axis3D();
    QVector3D axis_3D[6];
    QVector3D axisColor[6];
    void setup_Axis3D();

    // window setup
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
    bool bAutoRotate;
    bool bTimer3D;

    // Time
public:
    void setTimeDelta(const double &t_delta_){t_delta = t_delta_;}
    double getTimeDelta(){return t_delta;}
    double t; //time
    double t_delta;//time interval
    QTime time; // used just for calculating the frames per second

    // 3D graphs
public:
    QList<Graph3D> m_graph3DList;
    void addGraph3D(const Graph3D &graph3d_);

    // OpenGL stuff
protected:
    QOpenGLContext m_context;
    QOpenGLShaderProgram m_shaderProgram;
    QOpenGLBuffer m_vertexPositionBuffer;
    QOpenGLBuffer m_vertexColorBuffer;

};

#endif // GRAPH3D_OPENGL_H
