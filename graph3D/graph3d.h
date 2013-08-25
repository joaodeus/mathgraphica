#ifndef GRAPH3D_H
#define GRAPH3D_H


#include <QList>
#include <QString>
#include <QGLWidget>
#include <QOpenGLShaderProgram>


#include "calculator/calculator.h"

class Graph3D
{
public:
    Graph3D();
    ~Graph3D();


    QList<double> arrai_x;
    QList<double> arrai_y;
    QList<double> arrai_z;

    QString m_fxy;
    QString m_xmin;
    double m_xmindouble;
    QString m_xmax;
    double m_xmaxdouble;
    QString m_ymin;
    double m_ymindouble;
    QString m_ymax;
    double m_ymaxdouble;
    QString m_dxy;
    double m_dxdydouble;
    QString m_varx;
    QString m_vary;


private:
    QColor colorA;
    QColor colorB;
    QColor colorC;
    QColor colorD;

public:
    void setColorA(const QColor &color);
    void setColorB(const QColor &color);
    void setColorC(const QColor &color);
    void setColorD(const QColor &color);

    QColor getColorA();
    QColor getColorB();
    QColor getColorC();
    QColor getColorD();

   // Graph3D &operator=(const Graph3D & );  // Right side is the argument.

public:

    void draw(QOpenGLShaderProgram &m_shaderProgram, int &vertexAttrib, int &colorAttrib);
    bool SetGraph3D(const Graph3D &graph3D, double t);
    void UpdateGraphTime(double t);
    bool graph_has_variable_t();

    QVector3D *graph3D_fxy;
    QVector3D *graph3D_color_upper_face;
    QVector3D *graph3D_color_lower_face;
    //unsigned short *indices;

    bool bMemoryError;
    int k_x;
    int k_y;

};



#endif // GRAPH3D_H
