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
    format.setMajorVersion(3);
    format.setMinorVersion(0);
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


    backgroundColor.setRgbF(0.1f, 0.4f, 0.1f, 1.0f);

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

    axisColor[0].setX(1); axisColor[0].setY(0);axisColor[0].setZ(0);
    axisColor[1].setX(1); axisColor[1].setY(0);axisColor[1].setZ(0);
    axisColor[2].setX(0); axisColor[2].setY(1);axisColor[2].setZ(0);
    axisColor[3].setX(0); axisColor[3].setY(1);axisColor[3].setZ(0);
    axisColor[4].setX(0); axisColor[4].setY(0);axisColor[4].setZ(1);
    axisColor[5].setX(0); axisColor[5].setY(0);axisColor[5].setZ(1);
}

void Graph3D_OpenGL::initializeGl()
{
    m_context.makeCurrent(this);

    prepareShaderProgram();
    prepareVertexBuffers();
    //setGeometry();

    //glShadeModel(GL_FLAT);
    glEnable(GL_DEPTH_TEST);
    glFrontFace(GL_CCW);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);


    //glClearColor(backgroundColor.redF(),backgroundColor.greenF(), backgroundColor.blueF(), 0.0f);
    //glClearColor(0.1f, 0.4f, 0.1f, 1.0f);
    glClearColor(0.5,0.3,0,1);
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

    float positionData[] = {
        -0.8f, -0.8f, 0.0f,
         0.8f, -0.8f, 0.0f,
         0.0f,  0.8f, 0.0f
    };
    float colorData[] = {
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f
    };

    if (m_vertexPositionBuffer.create()) qDebug() << "Success creating vertex position buffer";
    m_vertexPositionBuffer.setUsagePattern(QOpenGLBuffer::StaticDraw);
    if (m_vertexPositionBuffer.bind()) qDebug() << "Success biding vertex position buffer";
    m_vertexPositionBuffer.allocate(positionData, 3 * 3 * sizeof(float));
   // m_vertexPositionBuffer.allocate(axis_3D, 3 * 6 * sizeof(float));


    if (m_vertexColorBuffer.create()) qDebug() << "Success creating vertex color buffer";
    m_vertexColorBuffer.setUsagePattern(QOpenGLBuffer::StaticDraw);
    if (m_vertexColorBuffer.bind()) qDebug() << "Success biding vertex color buffer";
    m_vertexColorBuffer.allocate(colorData, 3 * 3 * sizeof(float));
    //m_vertexColorBuffer.allocate(axisColor, 3 * 6 * sizeof(float));

    if (m_shaderProgram.bind()) qDebug() << "Success biding shader program";


    m_vertexPositionBuffer.bind();
    m_shaderProgram.enableAttributeArray("vertexPosition");
    m_shaderProgram.setAttributeBuffer("vertexPosition", GL_FLOAT, 0, 3);

    m_vertexColorBuffer.bind();
    m_shaderProgram.enableAttributeArray("VertexColor");
    m_shaderProgram.setAttributeBuffer("VertexColor", GL_FLOAT, 0, 3);

}

void Graph3D_OpenGL::setGeometry()
{
/*
    if (w <= h)
        projection.ortho(-(Range),Range,-Range*h/w,Range*h/w,-(Range*2),Range*2);
    else
        projection.ortho(-(Range*w/h),Range*w/h,-Range,Range,-(Range*2),Range*2);


    orientation.setToIdentity();
    orientation.translate(0.0f, 0.0f, 0.0f );
    orientation.rotate(xRot, 1.0f, 0.0f, 0.0f );
    orientation.rotate(yRot, 0.0f, 1.0f, 0.0f );
    orientation.rotate(zRot, 0.0f, 0.0f, 1.0f );
    orientation.scale(scale);

    // Set our newly created projection matrix to our shaderprogram
    m_shaderProgram.setUniformValue( "proj", projection );// Set projection to the shader
    // Set orientation matrix to the shaderprogram
    m_shaderProgram.setUniformValue( "matrix", orientation );
*/
}

void Graph3D_OpenGL::updateBackGroundColor(const QColor &color)
{
    backgroundColor=color;

    glClearColor(backgroundColor.redF(),backgroundColor.greenF(), backgroundColor.blueF(), 0.0f);
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
    //QTime stopwatch;
   // stopwatch.start();
    //qDebug()<<"real fps"<<frames /(time.elapsed() / 1000.0)/5;
    // Clear the background and depth-buffer for this frame
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glClear(GL_COLOR_BUFFER_BIT);


    QMatrix4x4 projection;
    QMatrix4x4 orientation;

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

    // Set our newly created projection matrix to our shaderprogram
    m_shaderProgram.setUniformValue( "proj", projection );// Set projection to the shader
    // Set orientation matrix to the shaderprogram
    m_shaderProgram.setUniformValue( "matrix", orientation );



    m_shaderProgram.bind();

    //glDrawArrays(GL_LINES,0 ,3);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    m_context.swapBuffers(this);
    //m_shaderProgram.release();


    //qDebug("time elapsed: %d", stopwatch.elapsed());
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
}

void Graph3D_OpenGL::axis3D(QOpenGLShaderProgram &m_sampleProgram, const GLint &vertexAttr,const GLint &colorAttr)
{



    ///////////////////////////////////////////////


    m_sampleProgram.setAttributeArray(vertexAttr, axis_3D, 0);
    m_sampleProgram.setAttributeArray(colorAttr, axisColor,0 );

    glDrawArrays(GL_LINES,0 ,6);

}

