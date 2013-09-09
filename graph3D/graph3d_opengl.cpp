#include "graph3d_opengl.h"

//#include <QCoreApplication>
#include <QTime>


//Graph3D_OpenGL::Graph3D_OpenGL()
Graph3D_OpenGL::Graph3D_OpenGL(QScreen *screen)
    : QWindow(screen)//, QOpenGLWidget(parent)
{

    setSurfaceType(OpenGLSurface);
  //  create();
    QSurfaceFormat format;
/*
    format.setDepthBufferSize(24);
    format.setMajorVersion(4);
    format.setMinorVersion(2);
    format.setSamples(4);
    format.setProfile(QSurfaceFormat::CoreProfile);
*/
    setFormat(format);
    create();


    //m_context = new QOpenGLContext;// Create an OpenGL context
    m_context.setFormat(format);
    m_context.create();

    // resize(QSize(800, 450));


    t=0;
    t_delta=0.5;

    xRot = 0;
    yRot = 0;
    zRot = 0;
    scale=1;

    AutoRotx = 0;
    AutoRoty = 0;
    AutoRotz = 0;

    TimerRotate = 0;
    Timer3D = 0;
    bAutoRotate = true;
    bTimer3D = false;

    // axis 3D
    Range = 1;


    //backgroundColor.setRgbF(0.1f, 0.4f, 0.1f, 1.0f);
    backgroundColor.setRgbF(0.0f, 0.0f, 0.0f, 1.0f);


    setup_Axis3D();
    initializeGl();
    resize(QSize(800, 450));

    connect(this, SIGNAL(widthChanged(int)), this, SLOT(resizeGl()));
    connect(this, SIGNAL(heightChanged(int)), this, SLOT(resizeGl()));

//    timer = new QTimer(this);
    //connect(timer, SIGNAL(timeout()), this, SLOT(paintGl()));
   // timer->start(16);


}

Graph3D_OpenGL::~Graph3D_OpenGL()
{
    timer->stop();
    delete timer;
}

void Graph3D_OpenGL::setup_Axis3D()
{
    axis_3D[0].setX(Range); axis_3D[0].setY(0.0f); axis_3D[0].setZ(0.0f);
    axis_3D[1].setX(-Range); axis_3D[1].setY(0.0f); axis_3D[1].setZ(0.0f);
    axis_3D[2].setX(0.0f); axis_3D[2].setY(Range); axis_3D[2].setZ(0.0f);
    axis_3D[3].setX(0.0f); axis_3D[3].setY(-Range); axis_3D[3].setZ(0.0f);
    axis_3D[4].setX(0.0f); axis_3D[4].setY(0.0f); axis_3D[4].setZ(Range);
    axis_3D[5].setX(0.0f); axis_3D[5].setY(0.0f); axis_3D[5].setZ(-Range);

    axisColor[0].setX(1); axisColor[0].setY(0.447059);axisColor[0].setZ(0);
    axisColor[1].setX(1); axisColor[1].setY(0.447059);axisColor[1].setZ(0);

    axisColor[2].setX(0.678431); axisColor[2].setY(1);axisColor[2].setZ(0.184314);//(173,255,47
    axisColor[3].setX(0.678431); axisColor[3].setY(1);axisColor[3].setZ(0.184314);

    axisColor[4].setX(0); axisColor[4].setY(1);axisColor[4].setZ(1);
    axisColor[5].setX(0); axisColor[5].setY(1);axisColor[5].setZ(1);
}

void Graph3D_OpenGL::initializeGl()
{
    m_context.makeCurrent(this);

    prepareShaderProgram();
    prepareVertexBuffers();
    setGeometry();

    //glShadeModel(GL_FLAT);
    glEnable(GL_DEPTH_TEST);
    glFrontFace(GL_CCW);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);


    glClearColor(backgroundColor.redF(),backgroundColor.greenF(), backgroundColor.blueF(), 1.0f);
    //glClearColor(0.1f, 0.4f, 0.1f, 1.0f);
    //glClearColor(0.5,0.3,0,1);
    //glClearColor(0.1f, 0.4f, 0.1f, 1.0f);


    paintGl();

}


void Graph3D_OpenGL::prepareShaderProgram()
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

void Graph3D_OpenGL::prepareVertexBuffers()
{
/*
    float positionData[] = {
        -0.8f, -0.8f, 0.0f,
         0.8f, -0.8f, 0.0f,
         0.0f,  0.8f, 0.0f
    };
    float colorData[] = {
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f
    };*/

    if (m_vertexPositionBuffer.create()) qDebug() << "Success creating vertex position buffer";
    m_vertexPositionBuffer.setUsagePattern(QOpenGLBuffer::StaticDraw);
    if (m_vertexPositionBuffer.bind()) qDebug() << "Success biding vertex position buffer";
    //m_vertexPositionBuffer.allocate(positionData, 3 * 3 * sizeof(float));
    m_vertexPositionBuffer.allocate(axis_3D, 3 * 6 * sizeof(float));


    if (m_vertexColorBuffer.create()) qDebug() << "Success creating vertex color buffer";
    m_vertexColorBuffer.setUsagePattern(QOpenGLBuffer::StaticDraw);
    if (m_vertexColorBuffer.bind()) qDebug() << "Success biding vertex color buffer";
    //m_vertexColorBuffer.allocate(colorData, 3 * 3 * sizeof(float));
    m_vertexColorBuffer.allocate(axisColor, 3 * 6 * sizeof(float));

    /*m_projectionBuffer.create();
    m_projectionBuffer.setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_projectionBuffer.allocate(&projection, 16 * sizeof(float));

    m_orientationBuffer.create();
    m_orientationBuffer.setUsagePattern(QOpenGLBuffer::DynamicDraw);
    m_orientationBuffer.allocate(&orientation, 16 * sizeof(float));
*/

    if (m_shaderProgram.bind()) qDebug() << "Success biding shader program";


    m_vertexPositionBuffer.bind();
    m_shaderProgram.enableAttributeArray("vertexPosition");
    m_shaderProgram.setAttributeBuffer("vertexPosition", GL_FLOAT, 0, 3);

    m_vertexColorBuffer.bind();
    m_shaderProgram.enableAttributeArray("VertexColor");
    m_shaderProgram.setAttributeBuffer("VertexColor", GL_FLOAT, 0, 3);


  /*  m_projectionBuffer.bind();
    //m_shaderProgram.enableAttributeArray("proj");
    m_shaderProgram.setUniformValue( "proj", projection );

    m_orientationBuffer.bind();
  //  m_shaderProgram.enableAttributeArray("matrix");
    m_shaderProgram.setUniformValue( "matrix", orientation );// Set orientation matrix to the shaderprogram
*/
  ////////////////////////////////////////////////////////

}

void Graph3D_OpenGL::setGeometry()
{       
    m_shaderProgram.setUniformValue( "proj", projection );// Set projection to the shader    
    m_shaderProgram.setUniformValue( "matrix", orientation );// Set orientation matrix to the shaderprogram
}

void Graph3D_OpenGL::updateBackGroundColor(const QColor &color)
{
    backgroundColor=color;

    glClearColor(backgroundColor.redF(),backgroundColor.greenF(), backgroundColor.blueF(), 1.0f);
}


void Graph3D_OpenGL::resizeGl()
{
    // Reset the GL viewport for current resolution.
    m_context.makeCurrent(this);
    w = width();
    h = height();
    glViewport(0,0, w, h);
    paintGl();
}


void Graph3D_OpenGL::paintGl()
{
    m_context.makeCurrent(this);
    QTime stopwatch;
    stopwatch.start();
    //qDebug()<<"real fps"<<frames /(time.elapsed() / 1000.0)/5;
    // Clear the background and depth-buffer for this frame
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glClear(GL_COLOR_BUFFER_BIT);


    projection.setToIdentity();

    if (width() <= height())
        projection.ortho(-(Range),Range,-Range*h/w,Range*h/w,-(Range*2),Range*2);
    else
        projection.ortho(-(Range*w/h),Range*w/h,-Range,Range,-(Range*2),Range*2);


    orientation.setToIdentity();
    orientation.translate(0.0f, 0.0f, 0.0f );
    orientation.rotate(xRot, 1.0f, 0.0f, 0.0f );
    orientation.rotate(yRot, 0.0f, 1.0f, 0.0f );
    orientation.rotate(zRot, 0.0f, 0.0f, 1.0f );
    orientation.scale(scale);

    m_shaderProgram.setUniformValue( "proj", projection );// Set projection to the shader
    m_shaderProgram.setUniformValue( "matrix", orientation );// Set orientation matrix to the shaderprogram



    //m_shaderProgram.bind();

    glDrawArrays(GL_LINES,0 ,6);
    //glDrawArrays(GL_TRIANGLES, 0, 6);

    m_context.swapBuffers(this);
    //m_shaderProgram.release();


    qDebug("time elapsed: %d", stopwatch.elapsed());
  /*  if (!(frames % 100)) {
        time.start();
        frames = 0;
    }
    frames ++;
*/

}

void Graph3D_OpenGL::hideEvent(QHideEvent * event)
{
    Q_UNUSED(event);
    qDebug("Hiding window");
    //destroy();
    //delete this;
    killTimer(TimerRotate);
    TimerRotate = 0;

    destroy();
}

void Graph3D_OpenGL::axis3D(QOpenGLShaderProgram &m_sampleProgram, const GLint &vertexAttr,const GLint &colorAttr)
{



    ///////////////////////////////////////////////


    m_sampleProgram.setAttributeArray(vertexAttr, axis_3D, 0);
    m_sampleProgram.setAttributeArray(colorAttr, axisColor,0 );

    glDrawArrays(GL_LINES,0 ,6);

}


void Graph3D_OpenGL::mousePressEvent(QMouseEvent *event)
{

    if (event->button() == Qt::LeftButton)
    {
        AutoRotx = AutoRoty = AutoRotz = 0;
        if (TimerRotate != 0)
        {
            killTimer(TimerRotate);
            TimerRotate = 0;
        }
        lastPos = event->pos();
    }
}

void Graph3D_OpenGL::mouseReleaseEvent (QMouseEvent * event )
{

    if (event->button() == Qt::LeftButton)
    {
        if ( !(AutoRotx==0 && AutoRoty==0 && AutoRotz==0) && bAutoRotate)
        {
            TimerRotate = startTimer(5);
        }
    }

}



void Graph3D_OpenGL::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons()== Qt::LeftButton )
    {
        xRot+=double(event->pos().y()-lastPos.y())/3.6;
        AutoRotx=double(event->pos().y()-lastPos.y())/3.6;

        yRot+=double(event->pos().x()-lastPos.x())/3.6;
        AutoRoty=double(event->pos().x()-lastPos.x())/3.6;

        zRot+=double(event->pos().x()-lastPos.x())/(3.6*3);
        zRot+=double(event->pos().y()-lastPos.y())/(3.6*3);
        AutoRotz=double(event->pos().x()-lastPos.x())/(3.6*3);
        AutoRotz+=double(event->pos().y()-lastPos.y())/(3.6*3);

        //updateGL();
        lastPos = event->pos();
        paintGl();
    }
}



void Graph3D_OpenGL::wheelEvent(QWheelEvent * event )
{
    if (event->delta()<0)
        if (scale > 0.01)
            scale/=1.25;

    if (event->delta()>0)
        if (scale < 20)
            scale*=1.25;

   // qDebug()<<scale;

    event->accept();
    paintGl();
}


bool Graph3D_OpenGL::event(QEvent *event)
{
    if (event->type() == QEvent::WindowDeactivate)
    {
        if (TimerRotate != 0)
        {
            killTimer(TimerRotate);
            TimerRotate = 0;
        }
    }


    ///////////////////////////////////////////////////
    //Zoom touch
    switch (event->type()) {
    case QEvent::TouchBegin:
    case QEvent::TouchUpdate:
    case QEvent::TouchEnd:
    {
        QTouchEvent *touchEvent = static_cast<QTouchEvent *>(event);
        QList<QTouchEvent::TouchPoint> touchPoints = touchEvent->touchPoints();
        if (touchPoints.count() == 2)
        {
            // determine scale factor
            const QTouchEvent::TouchPoint &touchPoint0 = touchPoints.first();
            const QTouchEvent::TouchPoint &touchPoint1 = touchPoints.last();
            qreal currentScaleFactor =
                    QLineF(touchPoint0.pos(), touchPoint1.pos()).length()
                    / QLineF(touchPoint0.startPos(), touchPoint1.startPos()).length();
            if (touchEvent->touchPointStates() & Qt::TouchPointMoved /*Qt::TouchPointReleased*/)
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
                //updateGL();
                paintGl();
            }

            //setTransform(QTransform().scale(totalScaleFactor * currentScaleFactor,
              //                              totalScaleFactor * currentScaleFactor));
        }
        return true;
    }
    default:
        break;
    }
    ///////////////////////////////////////////////////



    return QWindow::event(event);
}



void Graph3D_OpenGL::keyPressEvent(QKeyEvent *event)
{

    if (event->key() == Qt::Key_Up)
        xRot-=5;

    if (event->key() == Qt::Key_Down)
        xRot+=5;

    if (event->key() == Qt::Key_Left)
        yRot-=5;

    if (event->key() == Qt::Key_Right)
        yRot+=5;

    if (event->key() == Qt::Key_8)
        zRot-=5;

    if (event->key() == Qt::Key_9)
        zRot+=5;



    if (event->key() == Qt::Key_Minus)
        if (scale > 0.01)
            scale/=1.25;

    if (event->key() == Qt::Key_Plus)
        if (scale < 20)
            scale*=1.25;

    //updateGL();
    paintGl();

    QWindow::keyPressEvent(event);
}



void Graph3D_OpenGL::timerEvent(QTimerEvent *event)
{

    if (event->timerId() == TimerRotate)
    {
        AutoRotate();
        paintGl();
        //updateGL();
        return;
    }

    if(event->timerId() == Timer3D)
    {
        t+=t_delta;
        //m_graph3D.UpdateGraphTime(t);
        for(int i=0;i<m_graph3D_list.size();i++)
        {
            m_graph3D_list[i].UpdateGraphTime(t);
        }

        qDebug()<<t;
        paintGl();
        //updateGL();
        return;
    }

    QWindow::timerEvent(event);
}


void Graph3D_OpenGL::AutoRotate()
{

    double s=0.998;
    double xRot_old;
    double yRot_old;
    double diferencax;
    double diferencay;

    AutoRotx*=s;
    AutoRoty*=s;
    AutoRotz*=s;


    xRot_old=xRot;
    yRot_old=yRot;

    xRot+=AutoRotx;
    yRot+=AutoRoty;
    zRot+=AutoRotz;

    qDebug()<<xRot;
    qDebug()<<yRot;
    qDebug()<<zRot;



    /*if(xRot  > 3600)
    {
        xRot=xRot-3600;
    }*/

    diferencax=fabs(xRot_old-xRot);
    diferencay=fabs(yRot_old-yRot);
    if (diferencax < diferencay)
        diferencax=diferencay;

    if (diferencax<0.01)
    {
        if (TimerRotate != 0)
        {
            killTimer(TimerRotate);
            TimerRotate = 0;
        }
    }

  //  updateGL();
}
