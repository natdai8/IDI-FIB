// MyGLWidget.cpp
#include "MyGLWidget.h"
#include <iostream>
#include <stdio.h>

#define printOpenGLError() printOglError(__FILE__, __LINE__)
#define CHECK() printOglError(__FILE__, __LINE__,__FUNCTION__)
#define DEBUG() std::cout << __FILE__ << " " << __LINE__ << " " << __FUNCTION__ << std::endl;

int MyGLWidget::printOglError(const char file[], int line, const char func[])
{
    GLenum glErr;
    int    retCode = 0;

    glErr = glGetError();
    const char * error = 0;
    switch (glErr)
    {
        case 0x0500:
            error = "GL_INVALID_ENUM";
            break;
        case 0x501:
            error = "GL_INVALID_VALUE";
            break;
        case 0x502:
            error = "GL_INVALID_OPERATION";
            break;
        case 0x503:
            error = "GL_STACK_OVERFLOW";
            break;
        case 0x504:
            error = "GL_STACK_UNDERFLOW";
            break;
        case 0x505:
            error = "GL_OUT_OF_MEMORY";
            break;
        default:
            error = "unknown error!";
    }
    if (glErr != GL_NO_ERROR)
    {
        printf("glError in file %s @ line %d: %s function: %s\n",
                             file, line, error, func);
        retCode = 1;
    }
    return retCode;
}

MyGLWidget::~MyGLWidget() {
}

void MyGLWidget::initializeGL ()
{
    initializeOpenGLFunctions();

    glEnable (GL_DEPTH_TEST);

    glClearColor(0.5, 0.7, 1.0, 1.0); // defineix color de fons (d'esborrat)
    carregaShaders();
    creaBuffers();
    escala = 1.0f;

    ini_camera();
}

void MyGLWidget::carregaShaders ()
{
    BL2GLWidget::carregaShaders();
    projLoc = glGetUniformLocation(program->programId(), "proj");
    viewLoc = glGetUniformLocation(program->programId(), "view");
}

void MyGLWidget::paintGL ()
{
    // En cas de voler canviar els paràmetres del viewport, descomenteu la crida següent i
    // useu els paràmetres que considereu (els que hi ha són els de per defecte)
    //  glViewport (0, 0, ample, alt);

    // Esborrem el frame-buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Carreguem la transformació de model
    modelTransform ();

    // Activem el VAO per a pintar la caseta
    glBindVertexArray (VAO_Homer);

    // pintem
    glDrawArrays(GL_TRIANGLES, 0, m.faces().size() * 3);

    modelTransform2();

    // Activem el VAO per a pintar la caseta
    glBindVertexArray (VAO_Terra);

    // pintem
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glBindVertexArray (0);
}

void MyGLWidget::creaBuffers ()
{
  m.load("./models/HomerProves.obj");

  // Creació del Vertex Array Object per pintar
  glGenVertexArrays(1, &VAO_Homer);
  glBindVertexArray(VAO_Homer);

  GLuint VBO_Homer[2];
  glGenBuffers(2, VBO_Homer);
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Homer[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * m.faces().size() * 3 * 3,
               m.VBO_vertices(), GL_STATIC_DRAW);

  // Activem l'atribut vertexLoc
  glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(vertexLoc);

  glBindBuffer(GL_ARRAY_BUFFER, VBO_Homer[1]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * m.faces().size() * 3 * 3,
               m.VBO_matdiff(), GL_STATIC_DRAW);

  // Activem l'atribut colorLoc
  glVertexAttribPointer(colorLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(colorLoc);

  // -------------------------Terra
  glm::vec3 Vertices[6];
  Vertices[0] = glm::vec3(-2.0, -1.0, -2.0);
  Vertices[1] = glm::vec3(-2.0, -1.0, 2.0);
  Vertices[2] = glm::vec3(2.0, -1.0, 2.0);

  Vertices[3] = glm::vec3(2.0, -1.0, 2.0);
  Vertices[4] = glm::vec3(-2.0, -1.0, -2.0);
  Vertices[5] = glm::vec3(2.0, -1.0, -2.0);

  glGenVertexArrays(1, &VAO_Terra);
  glBindVertexArray(VAO_Terra);

  GLuint VBO_Terra;
  glGenBuffers(1, &VBO_Terra);
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Terra);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);

  // Activem l'atribut vertexLoc
  glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(vertexLoc);

  glBindVertexArray (0);
}

void MyGLWidget::projectTransform ()
{
    // glm::perspective (FOV en radians, ra window, znear, zfar);
    glm::mat4 Proj = glm::perspective (FOV, ra, znear, zfar);
    glUniformMatrix4fv (projLoc, 1, GL_FALSE, &Proj[0][0]);
}

void MyGLWidget::viewTransform()
{
    // glm::lookAt(OBS, VRP, UP);
    glm::mat4 View = glm::lookAt (OBS, VRP, UP);
    glUniformMatrix4fv (viewLoc, 1, GL_FALSE, &View[0][0]);
}

void MyGLWidget::ini_camera()
{
    // en este caso
    glm::vec3 Pmin(-2, -1, -2);
    glm::vec3 Pmax(2, 1, 2);

    centre = glm::vec3(Pmin + Pmax)/2.0f;
    radi = glm::distance(Pmin, Pmax)/2.0f;

    d = 2 * radi; // per exemple
    VRP = centre;
    OBS = VRP + d * glm::vec3(0, 0, 1); // direccio arbitraria per exemple en la z
    UP = glm::vec3(0,1,0); // de pie
    viewTransform();

    alfa_inicial = asin(radi / d);
    FOV = 2 * alfa_inicial;
    ra = 1.0f;
    znear = d - radi;
    zfar = d + radi;
    projectTransform();
}

void MyGLWidget::modelTransform()
{
    glm::mat4 TG(1.0);
    TG = glm::rotate(TG, r, glm::vec3(0, 1, 0));
    glUniformMatrix4fv(transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::modelTransform2()
{
    glm::mat4 TG(1.0);
    TG = glm::scale(TG, glm::vec3(1.0, 1.0, 1.0));
    glUniformMatrix4fv(transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::keyPressEvent(QKeyEvent* event)
{
  BL2GLWidget::keyPressEvent(event);
  makeCurrent();
  switch (event->key()) {
    case Qt::Key_R: { // escalar a més gran
      r += M_PI/4;
      break;
    }
    default: event->ignore(); break;
  }
  update();
}

// .h
  /*
   * MyGLWidget.h
    #include "BL2GLWidget.h"
    #include "./Model/model.h"

    class MyGLWidget : public BL2GLWidget {
    Q_OBJECT

    public:

        MyGLWidget(QWidget *parent=0) : BL2GLWidget(parent) {}
        ~MyGLWidget();

    private:

        int printOglError(const char file[], int line, const char func[]);

        GLuint projLoc, viewLoc;

        glm::vec3 OBS, VRP, UP;
        float FOV, ra, znear, zfar;

        Model m;
        GLuint VAO_Homer, VAO_Terra;

        float r = 1;

        glm::vec3 centre;
        float radi, d , alfa_inicial = 0;

    protected:

        virtual void carregaShaders ();
        virtual void projectTransform ();
        virtual void paintGL ();
        virtual void viewTransform ();

        virtual void initializeGL ();
        virtual void ini_camera();

        virtual void creaBuffers();

        virtual void modelTransform();
        virtual void keyPressEvent (QKeyEvent *event);
        virtual void modelTransform2 ();

    };

  */

// vertex shader

  /*
    uniform mat4 proj;
    uniform mat4 view;
    gl_Position = proj * view * TG * vec4 (vertex, 1.0);
  */
