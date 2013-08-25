#include "graph3d_opengl.h"

//#include <QCoreApplication>
#include <QTime>

Graph3D_OpenGL::Graph3D_OpenGL()
//Graph3D_OpenGL::Graph3D_OpenGL(QScreen *screen) : QWindow(screen)//, QOpenGLWidget(parent)
{

  /*  setSurfaceType(OpenGLSurface);
    create();
    // Create an OpenGL context
    m_context = new QOpenGLContext;
    //m_context->setFormat(format);
    m_context->create();

    // Make the context current on this window
    m_context->makeCurrent( this );
*/



    setAttribute(Qt::WA_AcceptTouchEvents);
    setAutoFillBackground( false );
    setAttribute (Qt::WA_OpaquePaintEvent);
    setAttribute( Qt::WA_NoSystemBackground );
    setAttribute( Qt::WA_NativeWindow );
    setAttribute( Qt::WA_PaintOnScreen, true );
    setAttribute( Qt::WA_StyledBackground,false);
    setAutoBufferSwap(true);


    t=0;
    t_delta=0.5;

    xRot = -60;
    yRot = -15;
    zRot = -25;
    scale=1;

    AutoRotx = 0;
    AutoRoty = 0;
    AutoRotz = 0;

    TimerRotate = 0;
    Timer3D = 0;
    bAutoRotate = true;
    bTimer3D = false;

    // axis 3D
    Range = 20;

    backgroundColor.setRgbF(0,0,0,1);

    // Setup scene and render it
   // initializeGL();
    //paintGL();
}


void Graph3D_OpenGL::initializeGL()
{
    //m_context->makeCurrent(this);
    //initializeOpenGLFunctions();

    //QGLFormat glFormat = QGLWidget::format();
    //if ( !glFormat.sampleBuffers() )
     //   qWarning() << "Could not enable sample buffers";



    // Create and compile the vertex-shader
    QOpenGLShader *vertex_shader = new QOpenGLShader(QOpenGLShader::Vertex, this);
    //vertex_shader->compileSourceCode(sample_vertex_shader_src);
    if (vertex_shader->compileSourceFile(":/shaders/shaders/vertexShaderES2.vsh"))
        qDebug() << "Vertex shader compilation Ok";
    else
        qDebug() << "Vertex shader compilation error: " << vertex_shader->log();



    // Create and compile the fragment-shader
    QOpenGLShader *fragment_shader = new QOpenGLShader(QOpenGLShader::Fragment, this);
    if (fragment_shader->compileSourceFile(":/shaders/shaders/fragmentShaderES2.fsh"))
        qDebug() << "Fragment shader compilation Ok";
    else
        qDebug() << "Fragment shader compilation error: " << fragment_shader->log();


    // Add vertex-shader to our program
    if (m_shaderProgram.addShader(vertex_shader))
        qDebug() << "Sucess adding vertex shader";
    else
        qDebug() << "Error adding vertex shader: " << m_shaderProgram.log();




    // Add fragment-shader to our program
    if (m_shaderProgram.addShader(fragment_shader))
        qDebug() << "Sucess adding fragment shader";
    else
        qDebug() << "Error adding fragment shader: " << m_shaderProgram.log();


    // Link our program. It's now ready for use.
    if (m_shaderProgram.link())
        qDebug() << "Sucess linking shader program";
    else
        qDebug() << "Error linking shader program: " << m_shaderProgram.log();





    //glShadeModel(GL_FLAT);
    glEnable(GL_DEPTH_TEST);
    glFrontFace(GL_CCW);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    //glClearColor(0.1f, 0.4f, 0.1f, 1.0f);
    glClearColor(backgroundColor.redF(),backgroundColor.greenF(), backgroundColor.blueF(), 0.0f);
}

void Graph3D_OpenGL::updateBackGroundColor(const QColor &color)
{
    backgroundColor=color;

    glClearColor(backgroundColor.redF(),backgroundColor.greenF(), backgroundColor.blueF(), 0.0f);
}


void Graph3D_OpenGL::resizeGL(int width_, int height_)
{
        // Reset the GL viewport for current resolution.
    w = width_;
    h = height_;
    glViewport(0,0, width_, height_);
}


void Graph3D_OpenGL::paintGL()
{
    //m_context->makeCurrent(this);
    QTime stopwatch;
    stopwatch.start();
    //qDebug()<<"real fps"<<frames /(time.elapsed() / 1000.0)/5;
    // Clear the background and depth-buffer for this frame
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


/*
    // Get the attribute locations from the shaderprogram
    GLint vertexAttr = m_shaderProgram.attributeLocation("vertex");
    GLint matrixAttr = m_shaderProgram.uniformLocation("matrix");
    GLint projAttr = m_shaderProgram.uniformLocation("proj");
    GLint colorAttr = m_shaderProgram.attributeLocation("VertexColor");
    // Set our own shaderprogram as an active one to GPU. There
    // can be only one active program at the time.
    m_shaderProgram.bind();


    QMatrix4x4 projection;
    // projection.perspective(45.0f, (float)width()/(float)height(), 0.1f, 20.0f );    // Use perspective projection

    if (w <= h)
        projection.ortho(-(Range),Range,-Range*h/w,Range*h/w,-(Range*2),Range*2);
    else
        projection.ortho(-(Range*w/h),Range*w/h,-Range,Range,-(Range*2),Range*2);


    // Set our newly created projection matrix to our shaderprogram
    m_shaderProgram.setUniformValue( projAttr, projection );// Set projection to the shader

    // Create orientation for the cube we are about to render
    QMatrix4x4 orientation;
    orientation.setToIdentity();
    // 4.5 units away from camera
   // orientation.translate(0.0f, 0.0f, -4.5f );
    orientation.translate(0.0f, 0.0f, 0.0f );
    orientation.rotate(xRot, 1.0f, 0.0f, 0.0f );
    orientation.rotate(yRot, 0.0f, 1.0f, 0.0f );
    orientation.rotate(zRot, 0.0f, 0.0f, 1.0f );
    orientation.scale(scale);
    // Set orientation matrix to the shaderprogram
    m_shaderProgram.setUniformValue( matrixAttr, orientation );

    // Set vertexarray to the shaderprogram
    m_shaderProgram.enableAttributeArray(vertexAttr);
    m_shaderProgram.enableAttributeArray(colorAttr);
*/


    QMatrix4x4 projection;
    // projection.perspective(45.0f, (float)width()/(float)height(), 0.1f, 20.0f );    // Use perspective projection

    if (w <= h)
        projection.ortho(-(Range),Range,-Range*h/w,Range*h/w,-(Range*2),Range*2);
    else
        projection.ortho(-(Range*w/h),Range*w/h,-Range,Range,-(Range*2),Range*2);

    // Create orientation for the cube we are about to render
    QMatrix4x4 orientation;
    orientation.setToIdentity();
    // 4.5 units away from camera
   // orientation.translate(0.0f, 0.0f, -4.5f );
    orientation.translate(0.0f, 0.0f, 0.0f );
    orientation.rotate(xRot, 1.0f, 0.0f, 0.0f );
    orientation.rotate(yRot, 0.0f, 1.0f, 0.0f );
    orientation.rotate(zRot, 0.0f, 0.0f, 1.0f );
    orientation.scale(scale);

    // Get the attribute locations from the shaderprogram
    GLint vertexAttr = m_shaderProgram.attributeLocation("vertex");
    GLint matrixAttr = m_shaderProgram.uniformLocation("matrix");
    GLint projAttr = m_shaderProgram.uniformLocation("proj");
    GLint colorAttr = m_shaderProgram.attributeLocation("VertexColor");
    // Set our own shaderprogram as an active one to GPU. There can be only one active program at the time.
    m_shaderProgram.bind();

    m_shaderProgram.setUniformValue( projAttr, projection );// Set projection matrix to the shader program in projAttr location
    m_shaderProgram.setUniformValue( matrixAttr, orientation );// Set orientation matrix to the shader program in matrixAttr location

    m_shaderProgram.enableAttributeArray(vertexAttr);// Set vertexarray to the shader program
    m_shaderProgram.enableAttributeArray(colorAttr); //Set colorAttr to the shader programa

    /////////////////////////////////////////////////////////////////////////////////////

    axis3D(m_shaderProgram,vertexAttr, colorAttr);

    //m_graph3D.draw(m_sampleProgram, vertexAttr, colorAttr);

    for (int i=0;i<m_graph3D_list.size();i++)
    {
        m_graph3D_list[i].draw(m_shaderProgram, vertexAttr, colorAttr);
    }



    m_shaderProgram.disableAttributeArray(vertexAttr);
    m_shaderProgram.disableAttributeArray(colorAttr);
    m_shaderProgram.release();


    qDebug("time elapsed: %d", stopwatch.elapsed());
  /*  if (!(frames % 100)) {
        time.start();
        frames = 0;
    }
    frames ++;
*/

}


void Graph3D_OpenGL::axis3D(QOpenGLShaderProgram &m_sampleProgram, const GLint &vertexAttr,const GLint &colorAttr)
{

    QVector3D axis_3D[6];

    axis_3D[0].setX(Range); axis_3D[0].setY(0.0f); axis_3D[0].setZ(0.0f);
    axis_3D[1].setX(-Range); axis_3D[1].setY(0.0f); axis_3D[1].setZ(0.0f);
    axis_3D[2].setX(0.0f); axis_3D[2].setY(Range); axis_3D[2].setZ(0.0f);
    axis_3D[3].setX(0.0f); axis_3D[3].setY(-Range); axis_3D[3].setZ(0.0f);
    axis_3D[4].setX(0.0f); axis_3D[4].setY(0.0f); axis_3D[4].setZ(Range);
    axis_3D[5].setX(0.0f); axis_3D[5].setY(0.0f); axis_3D[5].setZ(-Range);

    //axis[0]=v1;

    QVector3D cor[6];
    cor[0].setX(1); cor[0].setY(0);cor[0].setZ(0);
    cor[1].setX(1); cor[1].setY(0);cor[1].setZ(0);
    cor[2].setX(0); cor[2].setY(1);cor[2].setZ(0);
    cor[3].setX(0); cor[3].setY(1);cor[3].setZ(0);
    cor[4].setX(0); cor[4].setY(0);cor[4].setZ(1);
    cor[5].setX(0); cor[5].setY(0);cor[5].setZ(1);


    m_vertexArrayBuffer = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    if (m_vertexArrayBuffer->create())
        qDebug() << "Sucess creating vertex array buffer";
    else
        qDebug() << "Error creating vertex array buffer: " << m_sampleProgram.log();


    if (m_vertexArrayBuffer->bind())
        qDebug() << "Sucess binding vertex array buffer";
    else
        qDebug() << "Error biding vertex array buffer: " << m_sampleProgram.log();


    m_vertexArrayBuffer->setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_vertexArrayBuffer->allocate(&axis_3D, 6*sizeof(QVector3D));

    m_colorArrayBuffer = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    if (m_colorArrayBuffer->create())
        qDebug() << "Sucess creating color array buffer";
    else
        qDebug() << "Error creating color array buffer: " << m_sampleProgram.log();


    if (m_colorArrayBuffer->bind())
        qDebug() << "Sucess binding color array buffer";
    else
        qDebug() << "Error biding color array buffer: " << m_sampleProgram.log();


    m_colorArrayBuffer->setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_colorArrayBuffer->allocate(&cor,6*sizeof(QVector3D));


    ///////////////////////////////////////////////


    m_sampleProgram.setAttributeArray(vertexAttr, axis_3D, 0);
    m_sampleProgram.setAttributeArray(colorAttr, cor,0 );

    glDrawArrays(GL_LINES,0 ,6);

}

