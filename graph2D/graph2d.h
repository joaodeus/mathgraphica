#ifndef GRAPH2D_H
#define GRAPH2D_H

#include <QString>
#include <QList>
#include <QOpenGLBuffer>
#include <QVector3D>
#include <QOpenGLShaderProgram>
#include "calculator/calculator.h"

class Graph2D
{
public:
    Graph2D(Calculator *calc_);
    ~Graph2D();

    // set a graph from a math expression
    void setInterval(const double &min_, const double &max_);
    void setInterval(const QString &minExpression_, const QString &maxExpression_);
    void setDelta(const double delta_);
    void setDelta(const QString deltaExpression_);
    void setGraph2DExpression(const QString &expression_);

    // setupGraph() must be called after setInterval(), setDelta() and setGraph2DExpression()
    // it calculates and setup up the array's xx and yy
    bool setupGraph();


    // ... or set a graph from an array of values
    void setGraph2DArray(QList<double> &xx, QList<double> &yy);

    Graph2D &operator=(const Graph2D & );


private:

    QString m_graph2DExpression;
    QString m_xminExpression;
    double m_xmin;
    QString m_xmaxExpression;
    double m_xmax;
    QString m_deltaExpression;
    double m_delta;

    QList<double> xx;
    QList<double> yy;

    Calculator *calc;


    // drawing ---------------------------------------------
    QOpenGLBuffer m_vertexBufferGraph2D;
    QOpenGLBuffer m_colorBufferGraph2D;
    QVector3D *vertexPosition;
    QVector3D *vertexColor;
    QColor m_color;
public:
    void prepareBuffers();
    void setBufferData();
    void draw(QOpenGLShaderProgram &m_shaderProgram);
    void setColor(const QColor &color_);
    void setColor(const double &r, const double &g, const double &b);

};

#endif // GRAPH2D_H
