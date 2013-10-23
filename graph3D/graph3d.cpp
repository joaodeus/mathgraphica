#include "graph3d.h"

#include <QTime>

Graph3D::Graph3D()
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

    colorA.setRgbF(0,0.3,1,1);
    colorB.setRgbF(0,0.2,0.8,1);
    colorC.setRgbF(0.8,0.2,0,1);
    colorD.setRgbF(1,0.3,0,1);

    bufferSize = 0;

    vertexPosition  = NULL;
    vertexColor     = NULL;

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


void Graph3D::setGraph3DExpression(const QString &expression_)
{
    m_graph3DExpression = expression_;
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

    int xCount = (m_xmax - m_xmin) / m_delta + 1;
    int yCount = (m_ymax - m_ymin) / m_delta + 1;
    double x = m_xmin;
    double y = m_ymin;

    //for (int j = 0; j < yRows; j++)

    int i = 0; // index for array elements

    elements.clear();

    for (double y = m_ymin; y <= m_ymax; y += m_delta)
    {
        for (double x = m_xmin; x <= m_xmax; x += m_delta)
        {
            xx.append(x);
            yy.append(y);

            elements.append(i);
            elements.append(i + xCount);
            i++;
        }
    }

    calc.setVariable_Value(m_variable_X, xx);
    calc.setVariable_Value(m_variable_Y, yy);

    zz = calc.SolveExpression_list(m_graph3DExpression,xx.size());



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


bool Graph3D::SetGraph3D(const Graph3D &graph3D, double t)
{
/*
    Calculator calc;
    QMessageBox msgBox;

    colorA=graph3D.colorA;
    colorB=graph3D.colorB;
    colorC=graph3D.colorC;
    colorD=graph3D.colorD;


    calc.setVariable_Value("x",1); calc.setVariable_Value("y",1);
    calc.setVariable_Value("y",1);
    calc.setVariable_Value("t",1);
    calc.SolveExpression_fx(graph3D.m_graph3DExpression);
    //calc.fxyz(graph3D.m_fxy,1,"x",1,"y",1,"t");
    if (calc.error())
    {
        msgBox.setText(QObject::tr("Expression sintaxe error."));
        msgBox.exec();
        return false;
    }
    else
    {
        m_graph3DExpression = graph3D.m_graph3DExpression;
    }


    m_xmin=calc.SolveExpression(graph3D.m_xminExpression).numberReal();
    m_xmin=graph3D.m_xmin;
    if (calc.error())
    {
        msgBox.setText(QObject::tr("Invalid -x."));
        msgBox.exec();
        return false;
    }

    m_xmax=calc.SolveExpression(graph3D.m_xmaxExpression).numberReal();
    m_xmax=graph3D.m_xmax;
    if (calc.error())
    {
        msgBox.setText(QObject::tr("Invalid +x."));
        msgBox.exec();
        return false;
    }

    m_ymin=calc.SolveExpression(graph3D.m_yminExpression).numberReal();//calc.f(graph3D.m_ymin).r;
    m_ymin=graph3D.m_ymin;
    if (calc.error())
    {
        msgBox.setText(QObject::tr("Invalid -y."));
        msgBox.exec();
        return false;
    }

    m_ymax=calc.SolveExpression(graph3D.m_ymaxExpression).numberReal();//calc.f(graph3D.m_ymax).r;
    m_ymax=graph3D.m_ymax;
    if (calc.error())
    {
        msgBox.setText(QObject::tr("Invalid +y."));
        msgBox.exec();
        return false;
    }

    m_delta             = calc.SolveExpression(graph3D.m_deltaExpression).numberReal();//calc.f(graph3D.m_dxy).r;
    m_deltaExpression   = graph3D.m_delta;
    if (calc.error())
    {
        msgBox.setText(QObject::tr("Invalid dx, dy."));
        msgBox.exec();
        return false;
    }
    /////////////////////////////////////////////////////////////////////////////////////


    QTime stopwatch;
    stopwatch.start();

 //   stopwatch.restart();





    arrai_x.clear();
    arrai_y.clear();

    k_x = int( (m_xmax-m_xmin)/m_delta );
    k_y = int( (m_ymax-m_ymin)/m_delta );

    double x=m_xmin;
    double y=m_ymin;
    for (int i=0;i<k_x;i++)
    {
        y=m_ymin;
        for(int j=0;j<k_y;j++)
        {
            arrai_x.append(x);
            arrai_y.append(y);
            arrai_x.append(x+m_delta);
            arrai_y.append(y);
            y+=m_delta;
        }
        x+=m_delta;
    }



    //Complexo zz = calc.f_array_xy_t(m_fxy,m_varx,arrai_x,m_vary,arrai_y,z3D,t,"t");
    calc.setVariable_Value(m_variable_X, arrai_x);
    calc.setVariable_Value(m_variable_Y, arrai_y);
    calc.setVariable_Value("t", t);
    arrai_z = calc.SolveExpression_fx(m_graph3DExpression).numberListReal();


    qDebug("time array: %d", stopwatch.elapsed());

*/
    return true;
}


void Graph3D::UpdateGraphTime(double t)
{

    Calculator calc;

    QTime stopwatch;
    stopwatch.start();

    calc.setVariable_Value("t", t);
    //arrai_z = calc.SolveExpression_fx(m_graph3DExpression).numberListReal();

    qDebug("updating time array: %d", stopwatch.elapsed());

}

bool Graph3D::graph_has_variable_t()
{
    Calculator calc;
    return calc.isValid_Expression_with_time_variable(m_graph3DExpression);
}

void Graph3D::prepareBuffers()
{

}

void Graph3D::setBufferData(QOpenGLShaderProgram &m_shaderProgram)
{

}

void Graph3D::draw(QOpenGLShaderProgram &m_shaderProgram, int &vertexAttrb, int &colorAttrb)
{

    /*
    free(graph3D_fxy);
    free(graph3D_color_upper_face);
    free(graph3D_color_lower_face);


    graph3D_fxy = NULL;
    graph3D_color_upper_face = NULL;
    graph3D_color_lower_face = NULL;
    */





    /*
    int size = sizeof(QVector3D)*arrai_x.size();
    graph3D_fxy=(QVector3D*)malloc(size);
    if (graph3D_fxy == NULL)
    {
        qDebug()<<"Not enought memory";
        bMemoryError=true;
    }

    graph3D_color_upper_face =(QVector3D*)malloc(size);
    if (graph3D_color_upper_face == NULL)
    {
        free(graph3D_fxy);
        graph3D_fxy = NULL;
        qDebug()<<"Not enought memory";
        bMemoryError=true;
    }

    graph3D_color_lower_face =(QVector3D*)malloc(size);
    if (graph3D_color_lower_face == NULL)
    {
        free(graph3D_fxy);
        graph3D_fxy = NULL;
        free(graph3D_color_upper_face);
        graph3D_color_upper_face = NULL;
        qDebug()<<"Not enought memory";
        bMemoryError=true;
    }




    for (int i=0;i<arrai_x.size();i++)
    {
        graph3D_fxy[i].setX(arrai_x.at(i));
        graph3D_fxy[i].setY(arrai_y.at(i));
        graph3D_fxy[i].setZ(arrai_z.at(i));
    }




    bool cor = true;
    int i=0;
    int xi=0;
  //  double x=m_xmindouble;
  //  double y=m_ymindouble;
    for (int ii=0;ii<k_x;ii++)
    {
        if (xi%2 == 0)
            cor=true;
        else
            cor=false;
        xi++;

        for(int jj=0;jj<k_y;jj++)
        {
            if (cor)
            {
                graph3D_color_upper_face[i].setX(colorA.redF());
                graph3D_color_upper_face[i].setY(colorA.greenF());
                graph3D_color_upper_face[i].setZ(colorA.blueF());
                graph3D_color_lower_face[i].setX(colorC.redF());
                graph3D_color_lower_face[i].setY(colorC.greenF());
                graph3D_color_lower_face[i].setZ(colorC.blueF());
                i++;
                graph3D_color_upper_face[i].setX(colorA.redF());
                graph3D_color_upper_face[i].setY(colorA.greenF());
                graph3D_color_upper_face[i].setZ(colorA.blueF());
                graph3D_color_lower_face[i].setX(colorC.redF());
                graph3D_color_lower_face[i].setY(colorC.greenF());
                graph3D_color_lower_face[i].setZ(colorC.blueF());
                i++;
                cor=!cor;
            }
            else
            {
                graph3D_color_upper_face[i].setX(colorB.redF());
                graph3D_color_upper_face[i].setY(colorB.greenF());
                graph3D_color_upper_face[i].setZ(colorB.blueF());
                graph3D_color_lower_face[i].setX(colorD.redF());
                graph3D_color_lower_face[i].setY(colorD.greenF());
                graph3D_color_lower_face[i].setZ(colorD.blueF());
                i++;
                graph3D_color_upper_face[i].setX(colorB.redF());
                graph3D_color_upper_face[i].setY(colorB.greenF());
                graph3D_color_upper_face[i].setZ(colorB.blueF());
                graph3D_color_lower_face[i].setX(colorD.redF());
                graph3D_color_lower_face[i].setY(colorD.greenF());
                graph3D_color_lower_face[i].setZ(colorD.blueF());
                i++;
                cor=!cor;
            }
        }
        cor=!cor;
    }



    ////////////////////////////////////////////////////////////////////////////////////

    m_shaderProgram.setAttributeArray(vertexAttrb, graph3D_fxy, 0);
    m_shaderProgram.setAttributeArray(colorAttrb, graph3D_color_upper_face,0 );

    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);

    for (int i=0;i<k_x;i++)
    {
        glDrawArrays(GL_TRIANGLE_STRIP,i*(2*k_y),2*k_y);
    }

    m_shaderProgram.setAttributeArray(colorAttrb, graph3D_color_lower_face,0 );

    glCullFace(GL_FRONT);
    glEnable(GL_CULL_FACE);

    for (int i=0;i<k_x;i++)
    {
        glDrawArrays(GL_TRIANGLE_STRIP,i*(2*k_y),2*k_y);
    }


    ///////////////////////////////////////////////////////////
    free(graph3D_fxy);
    free(graph3D_color_upper_face);
    free(graph3D_color_lower_face);


    graph3D_fxy = NULL;
    graph3D_color_upper_face = NULL;
    graph3D_color_lower_face = NULL;
*/

}
