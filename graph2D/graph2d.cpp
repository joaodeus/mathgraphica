#include "graph2d.h"

Graph2D::Graph2D()
{
}


/*void IntegralDouble::setOuterLimits(const double &outerLowerLimit_, const double &outerUpperLimit_)
{
    outerLowerLimit = outerLowerLimit_;
    outerUpperLimit = outerUpperLimit_;
    outerLowerLimitExpression = QString("%1").arg(outerLowerLimit);
    outerUpperLimitExpression = QString("%1").arg(outerUpperLimit);
}

void IntegralDouble::setOuterLimits(const QString &outerLowerLimitExpression_, const QString &outerUpperLimitExpression_)
{
    outerLowerLimitExpression = outerLowerLimitExpression_;
    outerUpperLimitExpression = outerUpperLimitExpression_;

    outerLowerLimit = parser->SolveExpression(outerLowerLimitExpression).numberReal();
    if (parser->error())
    {
        QMessageBox::about(0,"Error!","Invalid outer lower limit");
    }

    outerUpperLimit = parser->SolveExpression(outerUpperLimitExpression).numberReal();
    if (parser->error())
    {
        QMessageBox::about(0,"Error!","Invalid outer upper limit");
    }

}*/

void Graph2D::setInterval(const double &min_, const double &max_)
{

}

void Graph2D::setInterval(const QString &minExpression_, const QString &maxExpression_)
{

}

void Graph2D::setDelta(const double delta_)
{

}

void Graph2D::setDelta(const QString deltaExpression_)
{

}

void Graph2D::setGraph2DExpression(const QString &expression_)
{}



void Graph2D::setGraph2DArray(QList<double> &xx, QList<double> &yy)
{}
