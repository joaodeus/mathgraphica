#ifndef GRAPH2D_H
#define GRAPH2D_H

#include <QString>
#include <QList>

class Graph2D
{
public:
    Graph2D();

    // set a graph from a math expression
    void setInterval(const double &min_, const double &max_);
    void setInterval(const QString &minExpression_, const QString &maxExpression_);
    void setDelta(const double delta_);
    void setDelta(const QString deltaExpression_);
    void setGraph2DExpression(const QString &expression_);

    // ... or set a graph from an array of values
    void setGraph2DArray(QList<double> &xx, QList<double> &yy);



private:

    QList<double> xx;
    QList<double> yy;

    QString m_graph2DExpression;
    QString m_xminExpression;
    double m_xmin;
    QString m_xmaxExpression;
    double m_xmax;
    QString m_deltaExpression;
    double m_delta;


};

#endif // GRAPH2D_H
