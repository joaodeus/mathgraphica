#ifndef GRAPH3DPARAMETRIC_H
#define GRAPH3DPARAMETRIC_H

#include <QString>
#include <QList>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include "calculator/calculator.h"

class Graph3DParametric
{
public:
    Graph3DParametric();


    QString getGraph3D_f1t_Expression()const{return m_graph3D_f1t_Expression;}
    QString getGraph3D_f2t_Expression()const{return m_graph3D_f2t_Expression;}
    QString getGraph3D_f3t_Expression()const{return m_graph3D_f3t_Expression;}

    QString getIntervaltMin()const{return m_tminExpression;}
    QString getIntervaltMax()const{return m_tmaxExpression;}
    QString getDelta()const{return m_deltaExpression;}


    // set a graph from a math expression
    void setGraph3D_f1t_Expression(const QString &f1t_expression_);
    void setGraph3D_f2t_Expression(const QString &f2t_expression_);
    void setGraph3D_f3t_Expression(const QString &f3t_expression_);

    void setMint(const double &min_t_);
    void setMint(const QString &min_tExpression_);

    void setMaxX(const double &max_t_);
    void setMaxX(const QString &max_tExpression_);

    void setDelta(const double delta_);
    void setDelta(const QString deltaExpression_);

    // setupGraph() must be called after setMin...(), setMax...(), setDelta() and setGraph3D_f1t_Expression()
    // it calculates and setup up the array's xx and yy
    bool setupGraph();


private:

    QList<double> xx;
    QList<double> yy;
    QList<double> zz;


    QString m_graph3D_f1t_Expression;
    QString m_graph3D_f2t_Expression;
    QString m_graph3D_f3t_Expression;


    QString m_tminExpression;
    double m_tmin;

    QString m_tmaxExpression;
    double m_tmax;

    QString m_deltaExpression;
    double m_delta;

    Calculator calc;

    double t; // time

    // drawing ---------------------------------------------
    QOpenGLBuffer m_vertexBufferGraph3D;
    QVector3D *vertexPosition;

    int bufferSize;
    QColor m_color;

public:
    void setColor(const QColor &color_);

    QColor getColor();

public:

    void prepareBuffers();
    void releaseBuffers();
    void setBufferData(QOpenGLShaderProgram &m_shaderProgram);
    void draw(QOpenGLShaderProgram &m_shaderProgram);

};

#endif // GRAPH3DPARAMETRIC_H
