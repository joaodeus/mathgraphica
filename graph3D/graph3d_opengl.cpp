#include "graph3d_opengl.h"

//#include <QCoreApplication>
#include <QTime>
#include <QFileDialog>
#include <QImageWriter>

Graph3D_OpenGL::Graph3D_OpenGL()
//Graph3D_OpenGL::Graph3D_OpenGL(QScreen *screen)
//    : QWindow(screen)//, QOpenGLWidget(parent)
{

//    setSurfaceType(OpenGLSurface);
  //  create();
  //  QSurfaceFormat format;
/*
    format.setDepthBufferSize(24);
    format.setMajorVersion(4);
    format.setMinorVersion(2);
    format.setSamples(4);
    format.setProfile(QSurfaceFormat::CoreProfile);
*/
    //setFormat(format);
    //create();


    //m_context = new QOpenGLContext;// Create an OpenGL context
  //  m_context.setFormat(format);
  //  m_context.create();

    // resize(QSize(800, 450));

    setAttribute(Qt::WA_AcceptTouchEvents);
    qDebug()<<"touch is: "<<testAttribute(Qt::WA_AcceptTouchEvents);

    t=0;
    t_delta=0.5;

    xRot = 0;
    yRot = 0;
    zRot = 0;
    scale=1;
    scaleX = scaleY = scaleZ = 1;
    minScale = 0.01;
    maxScale = 80;
    scaleDelta = 1.25;
    tx = 0;
    ty = 0;
    tz = 0;

    AutoRotx = 0;
    AutoRoty = 0;
    AutoRotz = 0;

    TimerRotate = 0;
    Timer3D = 0;
    bAutoRotate = true;
    bTimer3D = false;

    // axis 3D
    Range = 20;


    //backgroundColor.setRgbF(0.1f, 0.4f, 0.1f, 1.0f);
    backgroundColor.setRgbF(0.0f, 0.0f, 0.0f, 1.0f);


   // setup_Axis3D();
   // initializeGl();
  //  resize(QSize(800, 450));

  //  connect(this, SIGNAL(widthChanged(int)), this, SLOT(resizeGl()));
  //  connect(this, SIGNAL(heightChanged(int)), this, SLOT(resizeGl()));

//    timer = new QTimer(this);
    //connect(timer, SIGNAL(timeout()), this, SLOT(paintGl()));
   // timer->start(16);


}

Graph3D_OpenGL::~Graph3D_OpenGL()
{
    //timer->stop();
    //delete timer;
}



void Graph3D_OpenGL::initializeGL()
{
    //m_context.makeCurrent(this);
/*
    QGLFormat glFormat = QGLWidget::format();
    if ( !glFormat.sampleBuffers() )
        qWarning() << "Could not enable sample buffers";
*/

    setup_Axis3D();
    prepareShaderProgram();
    prepareVertexBuffers();

 //   setGeometry();


    //glShadeModel(GL_FLAT);
    glEnable(GL_DEPTH_TEST);
    glFrontFace(GL_CCW);
    glEnable(GL_CULL_FACE);
    //glCullFace(GL_BACK);
    glCullFace(GL_FRONT);


    glClearColor(backgroundColor.redF(),backgroundColor.greenF(), backgroundColor.blueF(), 0.0f);

    m_shaderProgram.bind();

  //  m_shaderProgram.bind();
   // paintGl();

}


void Graph3D_OpenGL::prepareShaderProgram()
{
    if (m_shaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex,":/shaders/shaders/vertShader3D.vsh"))
        qDebug() << "Sucess compiling and adding vertex shader";
    else
        qDebug() << "Error compiling and adding vertex shader: " << m_shaderProgram.log();


    if (m_shaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment,":/shaders/shaders/fragShader3D.fsh"))
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

    if (m_vertexPositionBuffer.create()) qDebug() << "Success creating vertex position buffer";
    m_vertexPositionBuffer.setUsagePattern(QOpenGLBuffer::StaticDraw);
    if (m_vertexPositionBuffer.bind()) qDebug() << "Success biding vertex position buffer";
    m_vertexPositionBuffer.allocate(axis_3D, 3 * 6 * sizeof(float));


    if (m_vertexColorBuffer.create()) qDebug() << "Success creating vertex color buffer";
    m_vertexColorBuffer.setUsagePattern(QOpenGLBuffer::StaticDraw);
    if (m_vertexColorBuffer.bind()) qDebug() << "Success biding vertex color buffer";
    m_vertexColorBuffer.allocate(axisColor, 3 * 6 * sizeof(float));


    if (m_shaderProgram.bind()) qDebug() << "Success biding shader program";


    m_vertexPositionBuffer.bind();
    m_shaderProgram.enableAttributeArray("vertexPosition");
    m_shaderProgram.setAttributeBuffer("vertexPosition", GL_FLOAT, 0, 3);

    m_vertexColorBuffer.bind();
    m_shaderProgram.enableAttributeArray("vertexColor");
    m_shaderProgram.setAttributeBuffer("vertexColor", GL_FLOAT, 0, 3);


}

void Graph3D_OpenGL::prepareGraphs()
{
    for (int i = 0; i < m_graph3DList.size(); i++)
    {
        m_graph3DList[i].prepareBuffers();
        m_graph3DList[i].setBufferData(m_shaderProgram);
    }

    updateGL();
}

void Graph3D_OpenGL::releaseGraphs()
{
    for (int i = 0; i < m_graph3DList.size(); i++)
    {
        m_graph3DList[i].releaseBuffers();
    }
}

void Graph3D_OpenGL::setBackGroundColor(const QColor &color)
{
    backgroundColor=color;
    glClearColor(backgroundColor.redF(),backgroundColor.greenF(), backgroundColor.blueF(), 1.0f);
    paintGL();
}

void Graph3D_OpenGL::SaveImageAs()
{
    QString filename;
    filename = QFileDialog::getSaveFileName( this,
                                            tr("Save File"),
                                            getenv( "HOME" ), tr(" Image (*.png)") );
                                            //getenv( "HOME" ), fileformat );

    if( !filename.endsWith( ".png" ) )
    {
        filename.append( ".png" );
    }

    QPixmap imagepix = renderPixmap( );
    QImage image = grabFrameBuffer( );
    QImageWriter imageWriter(filename,"png");

    //imageWriter.setQuality(100);

    if( imageWriter.canWrite() )
    {
        imageWriter.write(image);
    }
    else
    {
        QMessageBox::warning( this, tr("Save Image"), tr("Error saving image.") );
    }
}


void Graph3D_OpenGL::resizeGL(int width, int height)
{
    // Reset the GL viewport for current resolution.
    //m_context.makeCurrent(this);
    w = width;
    h = height;
    glViewport(0,0, width, height);
  //  paintGL();
}

void Graph3D_OpenGL::showEvent(QShowEvent *event)
{
    Q_UNUSED(event);
    prepareGraphs();
    time.start();
}

void Graph3D_OpenGL::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event);
    releaseGraphs();
}


void Graph3D_OpenGL::paintGL()
{
    //m_context.makeCurrent(this);

    int tt = time.elapsed();
    //qDebug("Time elapsed: %d ms", tt);
    if (tt != 0)
    {
        qDebug("Time elapsed: %d ms, Fps: %lf ", tt, double(1000/tt));
    }
    time.restart();

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
    //orientation.translate(0.0f, 0.0f, 0.0f );
    orientation.translate( tx, ty, tz );
    orientation.rotate(xRot, 1.0f, 0.0f, 0.0f );
    orientation.rotate(yRot, 0.0f, 1.0f, 0.0f );
    orientation.rotate(zRot, 0.0f, 0.0f, 1.0f );
    orientation.scale(scale);
    orientation.scale(scaleX, scaleY, scaleZ);


    m_shaderProgram.setUniformValue( "proj", projection );// Set projection to the shader
    m_shaderProgram.setUniformValue( "matrix", orientation );// Set orientation matrix to the shaderprogram



    //m_shaderProgram.bind();

    axis3D();

    for (int i = 0; i < m_graph3DList.size(); i++)
    {
        m_graph3DList[i].draw(m_shaderProgram);
    }



    //glDrawArrays(GL_TRIANGLES, 0, 6);

    //m_context.swapBuffers(this);
    //m_shaderProgram.release();




}



void Graph3D_OpenGL::setup_Axis3D()
{
    axis_3D[0].setX(Range); axis_3D[0].setY(0.0f); axis_3D[0].setZ(0.0f);
    axis_3D[1].setX(-Range); axis_3D[1].setY(0.0f); axis_3D[1].setZ(0.0f);
    axis_3D[2].setX(0.0f); axis_3D[2].setY(Range); axis_3D[2].setZ(0.0f);
    axis_3D[3].setX(0.0f); axis_3D[3].setY(-Range); axis_3D[3].setZ(0.0f);
    axis_3D[4].setX(0.0f); axis_3D[4].setY(0.0f); axis_3D[4].setZ(Range);
    axis_3D[5].setX(0.0f); axis_3D[5].setY(0.0f); axis_3D[5].setZ(-Range);

    axisColor[0].setX(1); axisColor[0].setY(0.4);axisColor[0].setZ(0);
    axisColor[1].setX(1); axisColor[1].setY(0.4);axisColor[1].setZ(0);
    axisColor[2].setX(0.6); axisColor[2].setY(1);axisColor[2].setZ(0.1);//(173,255,47
    axisColor[3].setX(0.6); axisColor[3].setY(1);axisColor[3].setZ(0.1);
    axisColor[4].setX(0); axisColor[4].setY(1);axisColor[4].setZ(1);
    axisColor[5].setX(0); axisColor[5].setY(1);axisColor[5].setZ(1);
}


void Graph3D_OpenGL::axis3D()
{
    //m_shaderProgram.bind();

    //if (m_vertexPositionBuffer.bind()) qDebug() << "Success biding vertex position buffer";
    m_vertexPositionBuffer.bind();
    // m_shaderProgram.enableAttributeArray("vertexPosition");
    m_shaderProgram.setAttributeBuffer("vertexPosition", GL_FLOAT, 0, 3);

    //if (m_vertexColorBuffer.bind()) qDebug() << "Success biding vertex color buffer";
    m_vertexColorBuffer.bind();
    //m_shaderProgram.enableAttributeArray("vertexColor");
    m_shaderProgram.setAttributeBuffer("vertexColor", GL_FLOAT, 0, 3);

    glDrawArrays(GL_LINES,0 ,6);

}


void Graph3D_OpenGL::hideEvent(QHideEvent * event)
{
    Q_UNUSED(event);
    qDebug("Hiding window");

    killTimer(TimerRotate);
    TimerRotate = 0;

    killTimer(Timer3D);
    Timer3D = 0;

   // destroy();
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
            if (bAutoRotate)
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
        updateGL();
    }
}



void Graph3D_OpenGL::wheelEvent(QWheelEvent * event )
{
    /*double minScale = 0.01;
    double maxScale = 20;
    double scaleDelta = 1.25;
*/
    if (event->delta() < 0)
        if (scale > minScale)
            scale /= scaleDelta;

    if (event->delta() > 0)
        if (scale < maxScale)
            scale *= scaleDelta;



    event->accept();
    updateGL();
}


bool Graph3D_OpenGL::event(QEvent *event)
{
    if (event->type() == QEvent::WindowDeactivate)
    {
        if (TimerRotate != 0)
        {
           // killTimer(TimerRotate);
           // TimerRotate = 0;
        }
    }


    ///////////////////////////////////////////////////
    //Zoom touch
    switch (event->type()) {
    case QEvent::TouchBegin:
    case QEvent::TouchUpdate:
    case QEvent::TouchEnd:
    {
        qDebug()<<"touch event";
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
                updateGL();
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


    return QGLWidget::event(event);
    //return QWindow::event(event);
}



void Graph3D_OpenGL::keyPressEvent(QKeyEvent *event)
{

    qDebug()<<event->key();
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


    // translate
    double translate_delta = 5;
    if (event->key() == Qt::Key_Q)
        tx -= translate_delta;
    if (event->key() == Qt::Key_W)
        tx += translate_delta;

    if (event->key() == Qt::Key_A)
        ty -= translate_delta;
    if (event->key() == Qt::Key_S)
        ty += translate_delta;

    if (event->key() == Qt::Key_Z)
        tz -= translate_delta;
    if (event->key() == Qt::Key_X)
        tz += translate_delta;




   /* double minScale = 0.01;
    double maxScale = 20;
    double scaleDelta = 1.25;
*/
    if (event->key() == Qt::Key_Minus)
        if (scale > minScale)
            scale /= scaleDelta;

    if (event->key() == Qt::Key_Plus)
        if (scale < maxScale)
            scale *= scaleDelta;


    // reduces x scale
    if (event->key() == Qt::Key_1)
        if (scaleX > minScale)
            scaleX /= scaleDelta;

    // expands x scale
    if (event->key() == Qt::Key_2)
        if (scaleX < maxScale)
            scaleX *= scaleDelta;

    // reduces y scale
    if (event->key() == Qt::Key_3)
        if (scaleY > minScale)
            scaleY /= scaleDelta;

    // expands y scale
    if (event->key() == Qt::Key_4)
        if (scaleY < maxScale)
            scaleY *= scaleDelta;


    // reduces z scale
    if (event->key() == Qt::Key_5)
        if (scaleZ > minScale)
            scaleZ /= scaleDelta;

    // expands z scale
    if (event->key() == Qt::Key_6)
        if (scaleZ < maxScale)
            scaleZ *= scaleDelta;



    updateGL();
    //paintGL();

    QGLWidget::keyPressEvent(event);
    //QWindow::keyPressEvent(event);
}

bool Graph3D_OpenGL::areTimeGraphs()
{
    for (int i = 0; i < m_graph3DList.size() ; i++)
    {
        if (m_graph3DList[i].isTimeGraph())
            return true;
    }
    return false;
}

void Graph3D_OpenGL::startStopTimer3D()
{
    if (Timer3D == 0 && areTimeGraphs())
    {
        Timer3D = startTimer(0);
        return;
    }

    if (Timer3D != 0)
    {
        killTimer(Timer3D);
        Timer3D = 0;
        t       = 0;
    }
}


void Graph3D_OpenGL::stopTimer3D()
{
    if (Timer3D != 0)
    {
        killTimer(Timer3D);
        Timer3D = 0;
        t       = 0;
    }
}

void Graph3D_OpenGL::setAutoRotation(const bool &autoRotation_)
{
    bAutoRotate = autoRotation_;

    if (bAutoRotate ==  false)
    {
        killTimer(TimerRotate);
        TimerRotate = 0;
    }
}

bool Graph3D_OpenGL::getAutoRotation()
{
    return bAutoRotate;
}

void Graph3D_OpenGL::timerEvent(QTimerEvent *event)

{

    if (event->timerId() == TimerRotate)
    {
        AutoRotate();
        updateGL();
        return;
    }

    if(event->timerId() == Timer3D)
    {
        t+=t_delta;
        //m_graph3D.UpdateGraphTime(t);
        for(int i = 0; i < m_graph3DList.size(); i++)
        {
            m_graph3DList[i].UpdateGraphTime(t, m_shaderProgram);
        }

        qDebug()<<t;
        updateGL();
        return;
    }

    QGLWidget::timerEvent(event);
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

   // qDebug()<<xRot;
   // qDebug()<<yRot;
   // qDebug()<<zRot;



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


void Graph3D_OpenGL::addGraph3D(const Graph3D &graph3d_)
{
    m_graph3DList.append(graph3d_);
}
