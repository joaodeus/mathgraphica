#include "graph3dparametric.h"

Graph3DParametric::Graph3DParametric()
{
    m_graph3D_f1t_Expression = "12*cos(t)";
    m_graph3D_f2t_Expression = "12*sin(t)";
    m_graph3D_f3t_Expression = "t";

    m_tminExpression = "0";
    m_tmin = 0;

    m_tmaxExpression = "100";
    m_tmax = 100;

    m_deltaExpression = "0.1";
    m_delta = 0.1;

    t = 0;

    m_color.setRgbF(1,0,0);
}



void Graph3DParametric::setColor(const QColor &color_)
{
    m_color = color_;
}

QColor Graph3DParametric::getColor()
{
    return m_color;
}



bool Graph3DParametric::setupGraph()
{
    return true;
}
