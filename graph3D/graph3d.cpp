#include "graph3d.h"

#include <QTime>

Graph3D::Graph3D() //:
//    m_vertexBufferGraph3D(QOpenGLBuffer::IndexBuffer),
  //  m_colorBufferGraph3D(QOpenGLBuffer::VertexBuffer)//,
    //m_iboBufferGraph3D(QOpenGLBuffer::IndexBuffer)
{

    /*
    m_fxy="cos(x)*sin(y)*cos(t)";
    m_xmin="-10";
    m_xmax="10";
    m_ymin="-10";
    m_ymax="10";
    m_dxy="0.5";
    m_varx="x";
    m_vary="y";*/



/*
    Red_a=0.0;      Green_a=0.2;    Blue_a=0.8; //azul claro
    Red_b=0.0;      Green_b=0.3;    Blue_b=1.0; //azul
    Red_c=0.8;      Green_c=0.2;    Blue_c=0.0; //vermelho
    Red_d=1.0;      Green_d=0.3;    Blue_d=0.0; //vermelho
*/

    timeGraph3D         = true;
    m_graph3DExpression = "cos(x)*sin(y)*cos(t)";

    m_xminExpression    = "-10";
    m_xmin              = -10;
    m_xmaxExpression    = "10";
    m_xmax              = 10;

    m_yminExpression    = "-10";
    m_ymin              = -10;
    m_ymaxExpression    = "10";
    m_ymax              = 10;

    m_deltaExpression   = "0.5";
    m_delta  = 0.5;

    m_variable_X        = "x";
    m_variable_Y        = "y";

    bPolarGraph         = false;
    t                   = 0;



    colorA.setRgbF(1,0,0,1);
    colorB.setRgbF(0,0,1,1);
    colorC.setRgbF(0,1,1,1);
    colorD.setRgbF(1,0.3,0.8,1);

    colorA.setRgbF(0,0.3,1,1);
    colorB.setRgbF(0,0.2,0.8,1);
    colorC.setRgbF(0.8,0.2,0,1);
    colorD.setRgbF(1,0.3,0,1);


    bufferSize = 0;

    vertexPosition  = NULL;
    vertexColor     = NULL;
    vertexBackColor = NULL;

    //graph3D_fxy = NULL;
    //graph3D_color_upper_face = NULL;
   // graph3D_color_lower_face = NULL;
   // indices = NULL;

    //bMemoryError=false;

  //  k_x = 0;
  //  k_y = 0;
}

Graph3D::~Graph3D()
{

}


void Graph3D::setMinX(const double &minX_)
{
    m_xmin = minX_;
    m_xminExpression = QString("%1").arg(minX_);

}

void Graph3D::setMinX(const QString &minXExpression_)
{
    m_xminExpression = minXExpression_;
    m_xmin = calc.SolveExpression(minXExpression_).numberReal();
    if (calc.error())
    {
        QMessageBox::about(0, QObject::tr("Error!"), QObject::tr("Invalid X min value in Graph3D"));
        return;
    }
}

void Graph3D::setMaxX(const double &maxX_)
{
    m_xmax = maxX_;
    m_xminExpression = QString("%1").arg(maxX_);

}

void Graph3D::setMaxX(const QString &maxXExpression_)
{
    m_xmaxExpression = maxXExpression_;
    m_xmax = calc.SolveExpression(maxXExpression_).numberReal();
    if (calc.error())
    {
        QMessageBox::about(0, QObject::tr("Error!"), QObject::tr("Invalid X max value in Graph3D"));
        return;
    }
}

void Graph3D::setMinY(const double &minY_)
{
    m_ymin = minY_;
    m_yminExpression = QString("%1").arg(minY_);
}

void Graph3D::setMinY(const QString &minYExpression_)
{
    m_yminExpression = minYExpression_;
    m_ymin = calc.SolveExpression(minYExpression_).numberReal();
    if (calc.error())
    {
        QMessageBox::about(0, QObject::tr("Error!"), QObject::tr("Invalid Y min value in Graph3D"));
        return;
    }
}

void Graph3D::setMaxY(const double &maxY_)
{
    m_ymax = maxY_;
    m_ymaxExpression = QString("%1").arg(maxY_);
}

void Graph3D::setMaxY(const QString &maxYExpression_)
{
    m_ymaxExpression = maxYExpression_;
    m_ymax = calc.SolveExpression(maxYExpression_).numberReal();
    if (calc.error())
    {
        QMessageBox::about(0, QObject::tr("Error!"), QObject::tr("Invalid Y max value in Graph3D"));
        return;
    }
}

void Graph3D::setDelta(const double delta_)
{
    m_delta = delta_;
    m_deltaExpression = QString("%1").arg(delta_);
}


void Graph3D::setDelta(const QString deltaExpression_)
{
    m_deltaExpression = deltaExpression_;
    m_delta = calc.SolveExpression(deltaExpression_).numberReal();
    if (calc.error())
    {
        QMessageBox::about(0, QObject::tr("Error!"), QObject::tr("Invalid delta value in Graph3D"));
        return;
    }
}

void Graph3D::setVariable1(const QString &variable1_)
{
    m_variable_X = variable1_;
}

void Graph3D::setVariable2(const QString &variable2_)
{
    m_variable_Y = variable2_;
}

void Graph3D::setGraph3DExpression(const QString &expression_)
{
    m_graph3DExpression = expression_;
    timeGraph3D = calc.isValid_Expression_with_time_variable(m_graph3DExpression);
}


bool Graph3D::setupGraph()
{

    xx.clear();
    yy.clear();
    zz.clear();


    QStringList variables;
    calc.GrabVariables(m_graph3DExpression, variables);

    if (variables.size() > 3)
    {
        //qDebug()<<"Error";
        return false;
    }

    xCount = ((m_xmax - m_xmin) / m_delta + 1) * 2;
    yCount = ((m_ymax - m_ymin) / m_delta + 1) * 2;
 //   double x = m_xmin;
  //  double y = m_ymin;


    elements.clear();

    double y;
    double x;
    for (y = m_ymin; y <= m_ymax; y += m_delta)
    {
        for (x = m_xmin; x <= m_xmax; x += m_delta)
        {
            xx.append(x);
            yy.append(y);

            //to refactor: remove the 2 following lines when using element indexes
            xx.append(x);
            yy.append(y+m_delta);
            //elements.append(i);
           // elements.append(i + xCount);
           // i++;
        }

        xx.append(x-m_delta);
        yy.append(y+m_delta);

        xx.append(m_xmin);
        yy.append(y+m_delta);


    }

    calc.setVariable_Value(m_variable_X, xx);
    calc.setVariable_Value(m_variable_Y, yy);
    calc.setVariable_Value("t",0);
    zz = calc.SolveExpression_list(m_graph3DExpression,xx.size());

    return true;
}

bool Graph3D::setupGraph2()
{

    xx.clear();
    yy.clear();
    zz.clear();


    QStringList variables;
    calc.GrabVariables(m_graph3DExpression, variables);

    if (variables.size() > 3)
    {
        //qDebug()<<"Error";
        return false;
    }

 //   xCount = ((m_xmax - m_xmin) / m_delta + 1) * 2;
   // yCount = ((m_ymax - m_ymin) / m_delta + 1) * 2;

    elements.clear();

    double y;
    double x;
   /* for (y = m_ymin; y <= m_ymax; y += m_delta)
    {

        for (x = m_xmin; x <= m_xmax; x += m_delta)
        {
            xx.append(x);
            yy.append(y);
        }
    }

    calc.setVariable_Value(m_variable_X, xx);
    calc.setVariable_Value(m_variable_Y, yy);
    calc.setVariable_Value("t",0);
    zz = calc.SolveExpression_list(m_graph3DExpression,xx.size());
*/

    // calculate elements indexes
    yCount = 0;
    for (y = m_ymin; y <= m_ymax; y += m_delta)
    {
        yCount++;
    }

    xCount = 0;
    for (x = m_xmin; x <= m_xmax; x += m_delta)
    {
        xCount++;
    }



    int i = 0;
    for (y = m_ymin; y <= m_ymax; y += m_delta)
    {
        for (x = m_xmin; x <= m_xmax; x += m_delta)
        {
            elements.append(i);
            elements.append(i+xCount);
            elements.append(i+1);

            elements.append(i+xCount);
            elements.append(i+1);
            elements.append(i+1+xCount);

            //////////////////////////////

            xx.append(x);
            yy.append(y);

            xx.append(x);
            yy.append(y+m_delta);

            xx.append(x+m_delta);
            yy.append(y);

            xx.append(x);
            yy.append(y+m_delta);

            xx.append(x+m_delta);
            yy.append(y);

            xx.append(x+m_delta);
            yy.append(y+m_delta);

            i++;
        }
        i++;
    }


    calc.setVariable_Value(m_variable_X, xx);
    calc.setVariable_Value(m_variable_Y, yy);
    calc.setVariable_Value("t",0);
    zz = calc.SolveExpression_list(m_graph3DExpression,xx.size());


    return true;

}


Graph3D &Graph3D::operator =(const Graph3D &a)
{

    xx                  = a.xx;
    yy                  = a.yy;
    zz                  = a.zz;
    elements            = a.elements;
    m_graph3DExpression = a.m_graph3DExpression;

    m_xminExpression    = a.m_xminExpression;
    m_xmin              = a.m_xmin;
    m_xmaxExpression    = a.m_xmaxExpression;
    m_xmax              = a.m_xmax;
    m_yminExpression    = a.m_yminExpression;
    m_ymin              = a.m_ymin;
    m_ymaxExpression    = a.m_ymaxExpression;
    m_ymax              = a.m_ymax;
    m_deltaExpression   = a.m_deltaExpression;
    m_delta             = a.m_delta;
    m_variable_X        = a.m_variable_X;
    m_variable_Y        = a.m_variable_Y;
    bufferSize          = a.bufferSize;
    colorA              = a.colorA;
    colorB              = a.colorB;
    colorC              = a.colorC;
    colorD              = a.colorD;

    return *this;
}


///////////////////////////////////////////////////////////////

void Graph3D::setColorA(const QColor &color)
{
    colorA=color;
}


void Graph3D::setColorB(const QColor &color)
{
    colorB=color;
}

void Graph3D::setColorC(const QColor &color)
{
    colorC=color;
}

void Graph3D::setColorD(const QColor &color)
{
    colorD=color;
}


QColor Graph3D::getColorA()
{
    return colorA;
}

QColor Graph3D::getColorB()
{
    return colorB;
}


QColor Graph3D::getColorC()
{
    return colorC;
}

QColor Graph3D::getColorD()
{
    return colorD;
}


void Graph3D::UpdateGraphTime(double t_, QOpenGLShaderProgram &m_shaderProgram)
{
    t = t_;

    QTime stopwatch;
    stopwatch.start();

    calc.setVariable_Value("t", t);
    zz = calc.SolveExpression_list(m_graph3DExpression,xx.size());

    setBufferData(m_shaderProgram);

    //qDebug("updating time array: %d", stopwatch.elapsed());

}

bool Graph3D::graph_has_variable_t()
{
    Calculator calc;
    return calc.isValid_Expression_with_time_variable(m_graph3DExpression);
}



void Graph3D::prepareBuffers()
{
    m_vertexBufferGraph3D.create();
    m_vertexBufferGraph3D.setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_vertexBufferGraph3D.bind();
    m_vertexBufferGraph3D.allocate(xx.size() * 3 * sizeof(float));

    m_colorBufferGraph3D.create();
    m_colorBufferGraph3D.setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_colorBufferGraph3D.bind();
    m_colorBufferGraph3D.allocate(xx.size() * 3 * sizeof(float));


    m_colorBackBufferGraph3D.create();
    m_colorBackBufferGraph3D.setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_colorBackBufferGraph3D.bind();
    m_colorBackBufferGraph3D.allocate(xx.size() * 3 * sizeof(float));

}


void Graph3D::prepareBuffers2()
{
    m_vertexBufferGraph3D.create();
    m_vertexBufferGraph3D.setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_vertexBufferGraph3D.bind();
    m_vertexBufferGraph3D.allocate(xx.size() * 3 * sizeof(float));

    m_colorBufferGraph3D.create();
    m_colorBufferGraph3D.setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_colorBufferGraph3D.bind();
    m_colorBufferGraph3D.allocate(elements.size() * 3 * sizeof(float));


    m_colorBackBufferGraph3D.create();
    m_colorBackBufferGraph3D.setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_colorBackBufferGraph3D.bind();
    m_colorBackBufferGraph3D.allocate(elements.size() * 3 * sizeof(float));


    m_elementsBufferGraph3D.create();
    m_elementsBufferGraph3D.setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_elementsBufferGraph3D.bind();
    m_elementsBufferGraph3D.allocate(elements.size() * sizeof(int));

}


void Graph3D::releaseBuffers()
{
    qDebug()<<"release buffers";
    m_vertexBufferGraph3D.release();
    m_colorBufferGraph3D.release();
    m_colorBackBufferGraph3D.release();
}

void Graph3D::releaseBuffers2()
{
    qDebug()<<"release buffers";
    m_vertexBufferGraph3D.release();
    m_colorBufferGraph3D.release();
    m_colorBackBufferGraph3D.release();
    m_elementsBufferGraph3D.release();
}


void Graph3D::setBufferData(QOpenGLShaderProgram &m_shaderProgram)
{

    int size = xx.size();
    if (vertexPosition == NULL)
        vertexPosition  = new QVector3D[ size ];

    if (vertexColor == NULL)
        vertexColor = new QVector3D[ size ];

    if (vertexBackColor == NULL)
        vertexBackColor = new QVector3D[ size ];


/*    if (vertexElements == NULL)
        vertexElements = new QVector3D[elements.size()];

    for (int j = 0; j < elements.size(); j++)
    {
        vertexElements[j] = elements.at(j);
    }*/

    bool bColor = true;
    int count_y = 0;
    for (int i = 0; i < size;i++)
    {

        bPolarGraph = false;
        if (bPolarGraph)
        {
            /*vertexPosition[i].setX( yy[i] * cos(xx.at(i)) );
            vertexPosition[i].setY( yy[i] * sin(xx.at(i)) );
            vertexPosition[i].setZ(0);*/
            vertexPosition[i].setX( sqrt( xx[i]*xx[i] + yy[i]*yy[i] + zz[i]*zz[i] ) );
            vertexPosition[i].setY( atan( yy[i]/xx[i] ) );
            vertexPosition[i].setZ( sqrt( xx[i]*xx[i] + yy[i]*yy[i] ) / zz[i] );
        }
        else
        {
            vertexPosition[i].setX(xx[i]);
            vertexPosition[i].setY(yy[i]);
            vertexPosition[i].setZ(zz[i]);
        }


        if (bColor)
        {

            vertexColor[i].setX(colorA.redF());
            vertexColor[i].setY(colorA.greenF());
            vertexColor[i].setZ(colorA.blueF());

            vertexBackColor[i].setX(colorC.redF());
            vertexBackColor[i].setY(colorC.greenF());
            vertexBackColor[i].setZ(colorC.blueF());

            bColor = !bColor;
        }
        else
        {
            vertexColor[i].setX(colorB.redF());
            vertexColor[i].setY(colorB.greenF());
            vertexColor[i].setZ(colorB.blueF());

            vertexBackColor[i].setX(colorD.redF());
            vertexBackColor[i].setY(colorD.greenF());
            vertexBackColor[i].setZ(colorD.blueF());

            bColor = !bColor;
        }


        count_y++;

        if (count_y > yCount+1)
        {
            bColor = !bColor;
            count_y  = 0;
        }



    }


    m_vertexBufferGraph3D.bind();
    m_vertexBufferGraph3D.write(0, vertexPosition, size * 3 * sizeof(float));
  //  m_shaderProgram.setAttributeBuffer("vertexPosition",GL_FLOAT,0, 3);

    m_colorBufferGraph3D.bind();
    m_colorBufferGraph3D.write(0,vertexColor, size * 3 * sizeof(float));
    //m_shaderProgram.setAttributeBuffer("vertexColor",GL_FLOAT,0, 3);


    m_colorBackBufferGraph3D.bind();
    m_colorBackBufferGraph3D.write(0,vertexBackColor, size * 3 * sizeof(float));
  //  m_shaderProgram.setAttributeBuffer("vertexColor",GL_FLOAT,0, 3);


    if (vertexPosition != NULL)
    {
        delete[] vertexPosition;
        vertexPosition = NULL;
      //  qDebug()<<"deleting buffer in graph2D";
    }

    if (vertexColor != NULL)
    {
        delete[] vertexColor;
        vertexColor = NULL;
    }

    if (vertexBackColor != NULL)
    {
        delete[] vertexBackColor;
        vertexBackColor = NULL;
    }

}



void Graph3D::setBufferData2(QOpenGLShaderProgram &m_shaderProgram)
{

    int size = xx.size();
    if (vertexPosition == NULL)
        vertexPosition  = new QVector3D[ size ];

    int size2 = elements.size();
    if (vertexColor == NULL)
        vertexColor = new QVector3D[ size2 ];

    if (vertexBackColor == NULL)
        vertexBackColor = new QVector3D[ size2 ];

    if (vertexElements == NULL)
        vertexElements = new GLint[size2];

    for (int i = 0; i < size; i++)
    {

        vertexPosition[i].setX(xx[i]);
        vertexPosition[i].setY(yy[i]);
        vertexPosition[i].setZ(zz[i]);
    }

    int i_aux = 0;

    for (int i = 0; i < size2; i++)
    {

        if ( i_aux < 3)
        {

            vertexColor[i].setX(colorA.redF());
            vertexColor[i].setY(colorA.greenF());
            vertexColor[i].setZ(colorA.blueF());

            vertexBackColor[i].setX(colorC.redF());
            vertexBackColor[i].setY(colorC.greenF());
            vertexBackColor[i].setZ(colorC.blueF());
        }
        else
        {
            vertexColor[i].setX(colorB.redF());
            vertexColor[i].setY(colorB.greenF());
            vertexColor[i].setZ(colorB.blueF());

            vertexBackColor[i].setX(colorD.redF());
            vertexBackColor[i].setY(colorD.greenF());
            vertexBackColor[i].setZ(colorD.blueF());
        }

        if (i_aux > 5)
            i_aux = 0;


        vertexElements[i] = elements.at(i);

    }


    m_vertexBufferGraph3D.bind();
    m_vertexBufferGraph3D.write(0, vertexPosition, size * 3 * sizeof(float));
  //  m_shaderProgram.setAttributeBuffer("vertexPosition",GL_FLOAT,0, 3);

    m_colorBufferGraph3D.bind();
    m_colorBufferGraph3D.write(0,vertexColor, size2 * 3 * sizeof(float));
    //m_shaderProgram.setAttributeBuffer("vertexColor",GL_FLOAT,0, 3);


    m_colorBackBufferGraph3D.bind();
    m_colorBackBufferGraph3D.write(0,vertexBackColor, size2 * 3 * sizeof(float));
  //  m_shaderProgram.setAttributeBuffer("vertexColor",GL_FLOAT,0, 3);

    m_elementsBufferGraph3D.write(0, vertexElements, size2 * sizeof(int));




    if (vertexPosition != NULL)
    {
        delete[] vertexPosition;
        vertexPosition = NULL;
      //  qDebug()<<"deleting buffer in graph2D";
    }

    if (vertexColor != NULL)
    {
        delete[] vertexColor;
        vertexColor = NULL;
    }

    if (vertexBackColor != NULL)
    {
        delete[] vertexBackColor;
        vertexBackColor = NULL;
    }

    if (vertexElements != NULL)
    {
        delete [] vertexElements;
        vertexElements = NULL;
    }
}


void Graph3D::draw(QOpenGLShaderProgram &m_shaderProgram)
{

  //  m_shaderProgram.bind();



    m_vertexBufferGraph3D.bind();
   // if (m_vertexBufferGraph2D.bind()) qDebug() << "Success biding vertex position buffer";
    //m_shaderProgram.enableAttributeArray("vertexPosition");
    m_shaderProgram.setAttributeBuffer("vertexPosition", GL_FLOAT, 0, 3);

    m_colorBufferGraph3D.bind();
    //m_shaderProgram.enableAttributeArray("vertexColor");
    m_shaderProgram.setAttributeBuffer("vertexColor", GL_FLOAT, 0, 3);


    glCullFace(GL_FRONT);
    //glDrawElements(GL_TRIANGLES, elements.size(), GL_FLOAT, elements);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, xx.size());
    //glDrawArrays(GL_TRIANGLE_STRIP, 0, 50);


    m_colorBackBufferGraph3D.bind();
//    m_shaderProgram.enableAttributeArray("vertexColor");
    m_shaderProgram.setAttributeBuffer("vertexColor", GL_FLOAT, 0, 3);


    glCullFace(GL_BACK);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, xx.size());

}

void Graph3D::draw2(QOpenGLShaderProgram &m_shaderProgram)
{

    m_vertexBufferGraph3D.bind();
   // if (m_vertexBufferGraph2D.bind()) qDebug() << "Success biding vertex position buffer";
    //m_shaderProgram.enableAttributeArray("vertexPosition");
    m_shaderProgram.setAttributeBuffer("vertexPosition", GL_FLOAT, 0, 3);

    m_colorBufferGraph3D.bind();
    //m_shaderProgram.enableAttributeArray("vertexColor");
    m_shaderProgram.setAttributeBuffer("vertexColor", GL_FLOAT, 0, 3);


    glCullFace(GL_FRONT);
    //glDrawElements(GL_TRIANGLES, elements.size(), GL_INT, vertexElements);

    glDrawArrays(GL_TRIANGLES, 0, xx.size());


    m_colorBackBufferGraph3D.bind();
//    m_shaderProgram.enableAttributeArray("vertexColor");
    m_shaderProgram.setAttributeBuffer("vertexColor", GL_FLOAT, 0, 3);


    glCullFace(GL_BACK);
//    glDrawElements(GL_TRIANGLES, elements.size(), GL_INT, vertexElements);

    glDrawArrays(GL_TRIANGLES, 0, xx.size());


}

void Graph3D::draw_aux(QOpenGLShaderProgram &m_shaderProgram)
{

  //  m_shaderProgram.bind();

    m_vertexBufferGraph3D.bind();
   // if (m_vertexBufferGraph2D.bind()) qDebug() << "Success biding vertex position buffer";
    //m_shaderProgram.enableAttributeArray("vertexPosition");
    m_shaderProgram.setAttributeBuffer("vertexPosition", GL_FLOAT, 0, 3);

  //  m_colorBufferGraph3D.bind();
    //m_shaderProgram.enableAttributeArray("vertexColor");
//    m_shaderProgram.setAttributeBuffer("vertexColor", GL_FLOAT, 0, 3);

    m_shaderProgram.disableAttributeArray("vertexColor");

    m_shaderProgram.setAttributeValue("vertexColor", colorA);
    glCullFace(GL_FRONT);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, xx.size());

    m_shaderProgram.setAttributeValue("vertexColor", colorB);
    glDrawArrays(GL_TRIANGLE_STRIP, 1, xx.size()-1);

    m_shaderProgram.setAttributeValue("vertexColor", colorC);
    glDrawArrays(GL_TRIANGLE_STRIP, 2, xx.size()-2);

    m_shaderProgram.setAttributeValue("vertexColor", colorD);
    glDrawArrays(GL_TRIANGLE_STRIP, 3, xx.size()-3);


  //  m_shaderProgram.setAttributeValue("vertexColor", colorC);
   // glDrawArrays(GL_TRIANGLES, 2, xx.size()-2);



    //glDrawArrays(GL_TRIANGLE_STRIP, 0, 50);


    //m_colorBackBufferGraph3D.bind();
//    m_shaderProgram.enableAttributeArray("vertexColor");
    //m_shaderProgram.setAttributeBuffer("vertexColor", GL_FLOAT, 0, 3);


   // glCullFace(GL_BACK);
 //   glDrawArrays(GL_TRIANGLE_STRIP, 0, xx.size());


}
