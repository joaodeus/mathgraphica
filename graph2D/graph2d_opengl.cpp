#include "graph2d_opengl.h"

Graph2D_OpenGL::Graph2D_OpenGL(Calculator *calc_): m_graph2D(calc_)
{
    calc = calc_;

    setMouseTracking(true);
    axis2Ddots = NULL;

    Range   = 20;
    scale   = 1;
    backgroundColor.setRgbF(0,0,0,1);

}

Graph2D_OpenGL::~Graph2D_OpenGL()
{
    delete[] dots;
    delete[] dotsColor;
}

void Graph2D_OpenGL::initializeGL()
{

    QGLFormat glFormat = QGLWidget::format();
    if ( !glFormat.sampleBuffers() )
        qWarning() << "Could not enable sample buffers";


    initializeAxis2D();
    prepareShaderProgram();
    prepareVertexBuffers();

    delete[] dots;
    delete[] dotsColor;

    //glShadeModel(GL_FLAT);
    glEnable(GL_DEPTH_TEST);
    glFrontFace(GL_CCW);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glClearColor(backgroundColor.redF(),backgroundColor.greenF(), backgroundColor.blueF(), 0.0f);
    //glClearColor(0.1f, 0.4f, 0.1f, 1.0f);


    // Set our own shaderprogram as an active one to GPU. There
    // can be only one active program at the time.
    m_shaderProgram.bind();
}

void Graph2D_OpenGL::prepareShaderProgram()
{
    if (m_shaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex,":/shaders/shaders/vertexShaderES2.vsh"))
        qDebug() << "Sucess compiling and adding vertex shader";
    else
        qDebug() << "Error compiling and adding vertex shader: " << m_shaderProgram.log();


    if (m_shaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment,":/shaders/shaders/fragmentShaderES2.fsh"))
        qDebug() << "Sucess compiling and adding fragment shader";
    else
        qDebug() << "Error compiling and adding fragment shader: " << m_shaderProgram.log();


    // Link our program. It's now ready for use.
    if (m_shaderProgram.link())
        qDebug() << "Sucess linking shader program";
    else
        qDebug() << "Error linking shader program: " << m_shaderProgram.log();
}

void Graph2D_OpenGL::prepareVertexBuffers()
{

    if (m_vertexPositionBuffer.create()) qDebug() << "Success creating vertex position buffer";
    m_vertexPositionBuffer.setUsagePattern(QOpenGLBuffer::StaticDraw);
    if (m_vertexPositionBuffer.bind()) qDebug() << "Success biding vertex position buffer";
    m_vertexPositionBuffer.allocate(axis2D, 3 * 4 * sizeof(float));


    if (m_vertexColorBuffer.create()) qDebug() << "Success creating vertex color buffer";
    m_vertexColorBuffer.setUsagePattern(QOpenGLBuffer::StaticDraw);
    if (m_vertexColorBuffer.bind()) qDebug() << "Success biding vertex color buffer";
    m_vertexColorBuffer.allocate(axisColor, 3 * 4 * sizeof(float));

    if (m_shaderProgram.bind()) qDebug() << "Success biding shader program";

    m_vertexPositionBuffer.bind();
    m_shaderProgram.enableAttributeArray("vertexPosition");
    m_shaderProgram.setAttributeBuffer("vertexPosition", GL_FLOAT, 0, 3);

    m_vertexColorBuffer.bind();
    m_shaderProgram.enableAttributeArray("VertexColor");
    m_shaderProgram.setAttributeBuffer("VertexColor", GL_FLOAT, 0, 3);

    //////////////////////////////////////////////////////////

    if (m_testeBufferPosition.create()) qDebug() << "Success creating vertex position buffer";
    m_testeBufferPosition.setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_testeBufferPosition.bind();
    m_testeBufferPosition.allocate(dots, number_of_dots * 3 * sizeof(float));



    if (m_testeBufferColor.create()) qDebug() << "Success creating vertex position buffer";
    m_testeBufferColor.setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_testeBufferColor.bind();
    m_testeBufferColor.allocate(dotsColor, number_of_dots * 3 * sizeof(float));

}


void Graph2D_OpenGL::initializeAxis2D()
{

    double r = 0;
    double g = 1;
    double b = 1;

    axis2D[0].setX(Range);  axis2D[0].setY(0.0f);   axis2D[0].setZ(0.0f);
    axis2D[1].setX(-Range); axis2D[1].setY(0.0f);   axis2D[1].setZ(0.0f);
    axis2D[2].setX(0.0f);   axis2D[2].setY(Range);  axis2D[2].setZ(0.0f);
    axis2D[3].setX(0.0f);   axis2D[3].setY(-Range); axis2D[3].setZ(0.0f);

    axisColor[0].setX(r);    axisColor[0].setY(g);    axisColor[0].setZ(b);
    axisColor[1].setX(r);    axisColor[1].setY(g);    axisColor[1].setZ(b);
    axisColor[2].setX(r);    axisColor[2].setY(g);    axisColor[2].setZ(b);
    axisColor[3].setX(r);    axisColor[3].setY(g);    axisColor[3].setZ(b);



    //////////////////////////////////////
    // Draw the white dots along the axis

    r = 1;
    g = 1;
    b = 1;

    double dist = 0.2 / scale;
    int dots_spacing = 1;
    int half_number_of_dots = 2 * (int(2*Range / dots_spacing) + 1 );
    number_of_dots = 2 * half_number_of_dots;

    dots = new QVector3D[number_of_dots];
    dotsColor = new QVector3D[number_of_dots];



    double x = -Range;

    for (int i=0;i<half_number_of_dots;i++)
    {
        if ( i % 5 == 0)
            dist = 0.4 / scale;
        else
            dist = 0.2 / scale;


        dotsColor[i].setX(r); dotsColor[i].setY(g); dotsColor[i].setZ(b);

        dots[i].setX(x); dots[i].setY(dist); dots[i].setZ(0);
        i++;
        dots[i].setX(x); dots[i].setY(-dist); dots[i].setZ(0);
        x += dots_spacing;

        dotsColor[i].setX(r); dotsColor[i].setY(g); dotsColor[i].setZ(b);
    }

    int ii = 0;
    double y = -Range;
    for (int i=half_number_of_dots;i<number_of_dots;i++)
    {
        if ( ii % 5 == 0)
            dist = 0.4 / scale;
        else
            dist = 0.2 / scale;

        ii += 2;

        dotsColor[i].setX(r); dotsColor[i].setY(g); dotsColor[i].setZ(b);

        dots[i].setX(-dist); dots[i].setY(y); dots[i].setZ(0);
        i++;
        dots[i].setX(dist); dots[i].setY(y); dots[i].setZ(0);
        y += dots_spacing;

        dotsColor[i].setX(r); dotsColor[i].setY(g); dotsColor[i].setZ(b);
    }

}



void Graph2D_OpenGL::resizeGL(int width, int height)
{
    w=width;
    h=height;
    glViewport(0,0, width, height);
}

void Graph2D_OpenGL::showEvent(QShowEvent *event)
{

    for (int i = 0; i < m_graph2DList.size(); i++)
    {
        m_graph2DList[i].setColor(1,0,0);
        m_graph2DList[i].prepareBuffers();
        m_graph2DList[i].setBufferData();
    }

    updateGL();
}

void Graph2D_OpenGL::paintGL()
{
    // Clear the background and depth-buffer for this frame
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    projection.setToIdentity();

    if (width() <= height())
        projection.ortho(-(Range),Range,-Range*h/w,Range*h/w,-(Range*2),Range*2);
    else
        projection.ortho(-(Range*w/h),Range*w/h,-Range,Range,-(Range*2),Range*2);


    orientation.setToIdentity();
    orientation.translate( translate_xy.x(), translate_xy.y(), 0.0f );
    orientation.scale( scale );

    m_shaderProgram.setUniformValue( "proj", projection );// Set projection to the shader
    m_shaderProgram.setUniformValue( "matrix", orientation );// Set orientation matrix to the shaderprogram



    drawAxis2D();

    for (int i = 0; i < m_graph2DList.size(); i++)
    {
        m_graph2DList[i].draw(m_shaderProgram);
    }

    //m_shaderProgram.bind();

    //glDrawArrays(GL_LINES,0 ,6);
}

void Graph2D_OpenGL::drawAxis2D()
{

    if (m_vertexPositionBuffer.bind()) qDebug() << "Success biding vertex position buffer";
    m_shaderProgram.enableAttributeArray("vertexPosition");
    m_shaderProgram.setAttributeBuffer("vertexPosition", GL_FLOAT, 0, 3);

    if (m_vertexColorBuffer.bind()) qDebug() << "Success biding vertex color buffer";
    m_shaderProgram.enableAttributeArray("VertexColor");
    m_shaderProgram.setAttributeBuffer("VertexColor", GL_FLOAT, 0, 3);


    glDrawArrays(GL_LINES,0 ,4);

    /////////////////////////////////////////////////////
    // Draw the white dots along the axis


    m_testeBufferPosition.bind();
    m_shaderProgram.enableAttributeArray("vertexPosition");
    m_shaderProgram.setAttributeBuffer("vertexPosition", GL_FLOAT, 0, 3);

    m_testeBufferColor.bind();
    m_shaderProgram.enableAttributeArray("VertexColor");
    m_shaderProgram.setAttributeBuffer("VertexColor", GL_FLOAT, 0, 3);

    glDrawArrays(GL_LINES, 0, number_of_dots);


}

void Graph2D_OpenGL::mousePressEvent(QMouseEvent *event)
{
#if !defined(Q_WS_S60)
{
    lastPos = MouseCoordinates_ToViewport(event->pos());
}
#endif
}

void Graph2D_OpenGL::mouseDoubleClickEvent(QMouseEvent * event)
{
    Q_UNUSED(event);
    scale   = 1;
    translate_xy.setX(0);
    translate_xy.setY(0);
    lastPos.setX(0);
    lastPos.setY(0);
    updateGL();
}


void Graph2D_OpenGL::mouseMoveEvent(QMouseEvent *event)
{
#if !defined(Q_WS_S60)
{
    if (event->buttons() == Qt::LeftButton || event->buttons() == Qt::RightButton)
    {
        translate_xy += (MouseCoordinates_ToViewport(event->pos()) - lastPos) * scale;
        updateGL();
    }
    lastPos = MouseCoordinates_ToViewport(event->pos());
}
#endif
}


void Graph2D_OpenGL::wheelEvent(QWheelEvent * event)
{
    if (event->delta()<0)
        if (scale > 0.05)
        {
            scale/=1.25;
            translate_xy += (MouseCoordinates_ToViewport(event->pos()) - lastPos)* scale;
        }

    if (event->delta()>0)
        if (scale < 20)
        {
            scale*=1.25;
            translate_xy += (MouseCoordinates_ToViewport(event->pos()) - lastPos)* scale;
        }

   // qDebug()<<scale;
    updateGL();
    event->accept();
}

bool Graph2D_OpenGL::event(QEvent *event)
{
    ///////////////////////////////////////////////////
    //Zoom touch
    switch (event->type()) {
    case QEvent::TouchBegin:
    {
        QTouchEvent *touchEvent = static_cast<QTouchEvent *>(event);
        QList<QTouchEvent::TouchPoint> touchPoints = touchEvent->touchPoints();

        if (touchPoints.count() == 1)
        {
            lastPos = MouseCoordinates_ToViewport(touchPoints.first().pos());
            event->accept();
            return true;
        }
        break;
    }
    case QEvent::TouchUpdate:
    {
        QTouchEvent *touchEvent = static_cast<QTouchEvent *>(event);
        QList<QTouchEvent::TouchPoint> touchPoints = touchEvent->touchPoints();

        if (touchPoints.count() == 1)
        {
            translate_xy += (MouseCoordinates_ToViewport(touchPoints.first().pos()) - lastPos) * scale;
            lastPos = MouseCoordinates_ToViewport(touchPoints.first().pos());
            updateGL();
            event->accept();
            return true;
        }

        if (touchPoints.count() == 2)
        {
            // determine scale factor
            const QTouchEvent::TouchPoint &touchPoint0 = touchPoints.first();
            const QTouchEvent::TouchPoint &touchPoint1 = touchPoints.last();
            qreal currentScaleFactor =
                    QLineF(touchPoint0.pos(), touchPoint1.pos()).length()
                    / QLineF(touchPoint0.startPos(), touchPoint1.startPos()).length();
           // if (touchEvent->touchPointStates() & Qt::TouchPointMoved /*Qt::TouchPointReleased*/)
            {
                // if one of the fingers is released, remember the current scale
                // factor so that adding another finger later will continue zooming
                // by adding new scale factor to the existing remembered value.


                scale *= currentScaleFactor;
                currentScaleFactor = 1;
                if (scale < 0.05)
                    scale=0.05;
                if (scale > 20)
                    scale=20;

                /*if (currentScaleFactor<1)
                    if (scale > 0.01)
                        scale/=1.1;

                if (currentScaleFactor>1)
                    if (scale < 20)
                        scale*=1.1;*/

                updateGL();
                event->accept();
                return true;
            }
            return true;
        }
        break;
    }
    case QEvent::TouchEnd:
    {
        break;
    }
    default:
        break;
    }
    ///////////////////////////////////////////////////

    return QGLWidget::event(event);
}

QPointF Graph2D_OpenGL::MouseCoordinates_ToViewport(const QPointF &p)
{
    int ww=width();
    int hh=height();
    double xx;
    double yy;

    if (ww <= hh)
    {
        xx = 2*Range/ww*p.x()-Range ;
        yy = -2*Range/ww*p.y()+Range*hh/ww;
    }
    else
    {
        xx = 2*Range/hh*p.x()-Range*ww/hh;
        yy = -2*Range/hh*p.y()+Range;
    }

    //return QPointF(xx,yy);
    return QPointF((xx - translate_xy.x()) / scale, (yy - translate_xy.y()) / scale);
}


void Graph2D_OpenGL::addGraph2D(const Graph2D &graph2d_)
{
    m_graph2D = graph2d_;
    m_graph2DList.append(graph2d_);

}
