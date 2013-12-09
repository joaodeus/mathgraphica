#include "graph2d.h"

#include <QDebug>

Graph2D::Graph2D()
{
    //calc = calc_;


    vertexPosition  = NULL;
    m_graphColor.setRgbF(1,0,0); // default color - red


    m_graph2DExpression_f1 = "12*cos(t)";
    m_graph2DExpression_f2 = "12*sin(2*t)";

    timeGraph2D         = true;
    m_graph2DExpression = "5*cos(x+t)";
    m_xminExpression    = "-50";
    m_xmin              = -50;
    m_xmaxExpression    = "50";
    m_xmax              = 50;
    m_deltaExpression   = "0.1";
    m_delta             = 0.1;
    t                   = 0;

    bPolarGraph         = false;
    bParametricGraph    = false;

    bufferSize = 0;

}

Graph2D::~Graph2D()
{
    if (vertexPosition != NULL)
        delete[] vertexPosition ;

}

void Graph2D::setInterval(const double &min_, const double &max_)
{
    m_xmin = min_;
    m_xmax = max_;
    m_xminExpression = QString("%1").arg(min_);
    m_xmaxExpression = QString("%1").arg(max_);
}

void Graph2D::setInterval(const QString &minExpression_, const QString &maxExpression_)
{
    m_xminExpression = minExpression_;
    m_xmaxExpression = maxExpression_;

    m_xmin = calc.SolveExpression(minExpression_).numberReal();
    if (calc.error())
    {
        QMessageBox::about(0, QObject::tr("Error!"), QObject::tr("Invalid min value in Graph2D"));
        return;
    }

    m_xmax = calc.SolveExpression(maxExpression_).numberReal();
    if (calc.error())
    {
        QMessageBox::about(0, QObject::tr("Error!"), QObject::tr("Invalid max value in Graph2D"));
        return;
    }
}

void Graph2D::setDelta(const double delta_)
{
    m_delta = delta_;
    m_deltaExpression = QString("%1").arg(delta_);
}

void Graph2D::setDelta(const QString deltaExpression_)
{
    m_deltaExpression = deltaExpression_;
    m_delta = calc.SolveExpression(deltaExpression_).numberReal();
    if (calc.error())
    {
        QMessageBox::about(0, QObject::tr("Error!"), QObject::tr("Invalid delta value in Graph2D"));
        return;
    }
}

void Graph2D::setGraph2DExpression(const QString &expression_)
{
    m_graph2DExpression = expression_;
    timeGraph2D = calc.isValid_Expression_with_time_variable(m_graph2DExpression);
}

void Graph2D::setGraph2DExpression_f1(const QString &expression_f1_)
{
    m_graph2DExpression_f1 = expression_f1_;
}

void Graph2D::setGraph2DExpression_f2(const QString &expression_f2_)
{
    m_graph2DExpression_f2 = expression_f2_;
}


bool Graph2D::setupGraph()
{
    if (isParametricGraph())
        return setupGraphParametric();

    xx.clear();
    yy.clear();

    QStringList variables;
    calc.GrabVariables(m_graph2DExpression, variables);

    if (variables.size() > 2)
    {        
        //qDebug()<<"Error";
        return false;
    }

    double x_aux = m_xmin;
    bufferSize = (m_xmax - m_xmin) / m_delta;
    for (int i = 0; i < bufferSize; i++)
    {
        xx.append(x_aux);
        x_aux += m_delta;
    }



    if (calc.isValid_Expression_with_time_variable(m_graph2DExpression) && (variables.size() == 2) )
    {
        calc.setVariable_Value("t", t);

        if (variables[0] == "t")
            calc.setVariable_Value(variables[1],xx);
        else
            calc.setVariable_Value(variables[0],xx);

        yy = calc.SolveExpression_list(m_graph2DExpression, xx.size());
        return true;
    }


    if (variables.size() == 1)
    {
        if (variables[0]== "t")
            calc.setVariable_Value("t", t);
        else
            calc.setVariable_Value(variables[0], xx);

        yy = calc.SolveExpression_list(m_graph2DExpression, xx.size());

        return true;
    }


    if (variables.size() == 0)
    {
        yy = calc.SolveExpression_list(m_graph2DExpression, xx.size());

        return true;
    }


    return false;

}

bool Graph2D::setupGraphParametric()
{
    xx.clear();
    yy.clear();


    QStringList variables_f1;
    calc.GrabVariables(m_graph2DExpression_f1, variables_f1);
    if (variables_f1.size() > 2)
    {
        //qDebug()<<"Error";
        return false;
    }


    QStringList variables_f2;
    calc.GrabVariables(m_graph2DExpression_f2, variables_f2);
    if (variables_f2.size() > 2)
    {
        return false;
    }

    if (variables_f1.size() == 1 && variables_f2.size() == 1)
    {
        if (variables_f1[0] != variables_f2[0]) // error, variables from f1 and f2 mismatch
            return false;
    }

    QList<double> tt;
    double x_aux = m_xmin;
    bufferSize = (m_xmax - m_xmin) / m_delta;
    for (int i = 0; i < bufferSize; i++)
    {
        tt.append(x_aux);
        x_aux += m_delta;
    }


    if (calc.isValidExpression(m_graph2DExpression_f1) || calc.isValidExpression_ft(m_graph2DExpression_f1))
    {
        if (variables_f1.size() == 1)
        {
            calc.setVariable_Value(variables_f1[0], tt);
        }
        xx = calc.SolveExpression_list(m_graph2DExpression_f1, tt.size());
    }
    else
    {
        return false;
    }



    if (calc.isValidExpression(m_graph2DExpression_f2) || calc.isValidExpression_ft(m_graph2DExpression_f2))
    {
        if (variables_f2.size() == 1)
        {
            calc.setVariable_Value(variables_f2[0], tt);
        }
        yy = calc.SolveExpression_list(m_graph2DExpression_f2, tt.size());
    }
    else
    {
        return false;
    }


    return false;
}


void Graph2D::setGraph2DArray(QList<double> &xx_, QList<double> &yy_)
{
    xx          = xx_;
    yy          = yy_;
    bufferSize  = xx.size();
}

Graph2D &Graph2D::operator =(const Graph2D &a)
{
    m_graph2DExpression_f1  = a.m_graph2DExpression_f1;
    m_graph2DExpression_f2  = a.m_graph2DExpression_f2;
    m_graph2DExpression     = a.m_graph2DExpression;
    m_xminExpression        = a.m_xminExpression;
    m_xmin                  = a.m_xmin;
    m_xmaxExpression        = a.m_xmaxExpression;
    m_xmax                  = a.m_xmax;
    m_deltaExpression       = a.m_deltaExpression;
    m_delta                 = a.m_delta;
    xx                      = a.xx;
    yy                      = a.yy;
    m_graphColor            = a.m_graphColor;
    bPolarGraph             = a.bPolarGraph;
    bParametricGraph        = a.bParametricGraph;
    bufferSize              = a.bufferSize;

    return *this;
}


void Graph2D::setPolarGraph(const bool &bPolarGraph_)
{
    bPolarGraph = bPolarGraph_;

    if (bPolarGraph)
        setParametric(false);
}

bool Graph2D::isPolarGraph()
{
    return bPolarGraph;
}

void Graph2D::setParametric(const bool &bParametricGraph_)
{
    bParametricGraph = bParametricGraph_;

    if (bParametricGraph)
        setPolarGraph(false);
}

bool Graph2D::isParametricGraph()
{
    return bParametricGraph;
}


void Graph2D::UpdateGraphTime(double t_, QOpenGLShaderProgram &m_shaderProgram)
{
    t = t_;
    if (isTimeGraph() == false)
        return;

    calc.setVariable_Value("t", t);
    yy = calc.SolveExpression_list(m_graph2DExpression, xx.size());


    setBufferData(m_shaderProgram);
}


////////////////////////////////////////////////////////

void Graph2D::prepareBuffers()
{
    //if (m_vertexBufferGraph2D.create()) qDebug() << "Success creating graph2D vertex position buffer";
    //else qDebug()<<"vertex buffer failed to create";
    m_vertexBufferGraph2D.create();
    m_vertexBufferGraph2D.setUsagePattern(QOpenGLBuffer::StaticDraw);

    //if (m_vertexBufferGraph2D.bind()) qDebug() << "Success biding vertex position buffer";
    m_vertexBufferGraph2D.bind();
    m_vertexBufferGraph2D.allocate(bufferSize * 3 * sizeof(float));
}

void Graph2D::releaseBuffers()
{
    //qDebug()<<"release buffers";
    m_vertexBufferGraph2D.release();
}


void Graph2D::setBufferData(QOpenGLShaderProgram &m_shaderProgram)
{
    int size = xx.size();


    if (vertexPosition == NULL)
    {
        vertexPosition  = new QVector3D [size];
       // qDebug()<<"creating buffer in graph2D";
    }
  /*  else
    {
        delete[] vertexPosition;
        //delete vertexPosition;
        vertexPosition  = new QVector3D [size];
    }
*/

    if (bPolarGraph)
    {
        for (int i = 0; i < size;i++)
        {

            vertexPosition[i].setX( yy[i] * cos(xx.at(i)) );
            vertexPosition[i].setY( yy[i] * sin(xx.at(i)) );
            vertexPosition[i].setZ(0);
        }
    }
    else
    {
        double infinity = 200;
        int interval_size_between_poles = 0;
        poles_interval.clear();
        poles_interval.append(0);

        for (int i = 0; i < size - 2;i++)
        {

            interval_size_between_poles++;

            vertexPosition[i].setX(xx[i]);
            vertexPosition[i].setY(yy[i]);
            vertexPosition[i].setZ(0);

            if ( (yy[i] * yy[i+1] < 0) &&  ( fabs(yy[i] -yy[i+1] ) > fabs(yy[i] -yy[i+2]) ) )
            {
                // save infinity poles
                if (yy[i] < 0)
                {
                    vertexPosition[i].setY(-infinity);
                    vertexPosition[i+1].setY(infinity);

                    vertexPosition[i+1].setX(xx[i+1]);
                }
                else
                {
                    vertexPosition[i].setY(infinity);
                    vertexPosition[i+1].setY(-infinity);

                    vertexPosition[i+1].setX(xx[i+1]);
                }

                poles_interval.append(interval_size_between_poles);
                poles_interval.append(i+1);
                interval_size_between_poles = 1;

                i++;
            }
        }

        poles_interval.append(interval_size_between_poles );

    }




    //////////////////////////////////////////////////////

    m_vertexBufferGraph2D.bind();
    //if (m_vertexBufferGraph2D.bind()) qDebug() << "setBufferData() - Success biding vertex position graph 2D buffer";
    //else qDebug()<<"setBufferData() - something wrong";
//    m_vertexBufferGraph2D.allocate(vertexPosition, size * 3 * sizeof(float));
    m_vertexBufferGraph2D.write(0, vertexPosition, size * 3 * sizeof(float));

  //  m_shaderProgram.disableAttributeArray("vertexColor");
    m_shaderProgram.setAttributeValue("vertexColor", m_graphColor);


    if (vertexPosition != NULL)
    {
        delete[] vertexPosition;
        vertexPosition = NULL;
      //  qDebug()<<"deleting buffer in graph2D";
    }

}




void Graph2D::draw(QOpenGLShaderProgram &m_shaderProgram)
{

  //  prepareBuffers();


    /////////////////////////////////////

    m_shaderProgram.bind();
    m_vertexBufferGraph2D.bind();
   // if (m_vertexBufferGraph2D.bind()) qDebug() << "Success biding vertex position buffer";
    m_shaderProgram.enableAttributeArray("vertexPosition");
    m_shaderProgram.setAttributeBuffer("vertexPosition", GL_FLOAT, 0, 3);

    m_shaderProgram.disableAttributeArray("vertexColor");
    m_shaderProgram.setUniformValue("vertexColor", m_graphColor);

    if (bPolarGraph)
    {
        glDrawArrays(GL_LINE_STRIP, 0, xx.size());
    }
    else
    {
        for (int i=0;i<poles_interval.size();i=i+2)
        {
            glDrawArrays(GL_LINE_STRIP, poles_interval[i],poles_interval[i+1]);
        }
    }

    //////////////////////////////////////////////

   // releaseBuffers();


}

void Graph2D::setColor(const QColor &color_)
{
    m_graphColor = color_;
}

void Graph2D::setColor(const double &r, const double &g, const double &b)
{
    m_graphColor.setRgbF(r,g,b);
    //m_graphColor.setAlphaF(1);
}
