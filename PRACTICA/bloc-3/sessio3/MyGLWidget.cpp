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
  // Cal inicialitzar l'ús de les funcions d'OpenGL
  initializeOpenGLFunctions();

  glClearColor(0.5, 0.7, 1.0, 1.0); // defineix color de fons (d'esborrat)
  glEnable(GL_DEPTH_TEST);
  carregaShaders();
  creaBuffersPatricio();
  creaBuffersTerraIParet();

  posFocus = glm::vec3(0, 0, 0); // camara
  glUniform3fv (posFocusLoc, 1, &posFocus[0]);

  colorFocus = glm::vec3(0.8, 0.8, 0.8);
  glUniform3fv (colorFocusLoc, 1, &colorFocus[0]);

  posFocusEsc = glm::vec3(0, -0.5, 0); // escena 0.85-0.3
  glUniform3fv (posFocusLocEsc, 1, &posFocusEsc[0]);

  colorFocusEsc = glm::vec3(0.8, 0.8, 0.0);
  glUniform3fv (colorFocusLocEsc, 1, &colorFocusEsc[0]);

  escena = 1;
  glUniform1i(escenaLoc, escena);

  suelo = glm::vec3(0.0, -0.85, 0.0);

  iniEscena();
  iniCamera();
}

void MyGLWidget::paintGL ()
{
  // En cas de voler canviar els paràmetres del viewport, descomenteu la crida següent i
  // useu els paràmetres que considereu (els que hi ha són els de per defecte)
  // glViewport (0, 0, ample, alt);

  // Esborrem el frame-buffer i el depth-buffer
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Activem el VAO per a pintar el terra
  glBindVertexArray (VAO_Terra);

  modelTransformTerra ();
  // pintem el terra
  glDrawArrays(GL_TRIANGLES, 0, 12);

  // Activem el VAO per a pintar el Patricio
  glBindVertexArray (VAO_Patr);

  modelTransformPatricio ();
  // Pintem el Patricio
  glDrawArrays(GL_TRIANGLES, 0, patr.faces().size()*3);

  glBindVertexArray(0);
}

void MyGLWidget::calculaCapsaModel ()
{
  // Càlcul capsa contenidora i valors transformacions inicials
  float minx, miny, minz, maxx, maxy, maxz;
  minx = maxx = patr.vertices()[0];
  miny = maxy = patr.vertices()[1];
  minz = maxz = patr.vertices()[2];
  for (unsigned int i = 3; i < patr.vertices().size(); i+=3)
  {
    if (patr.vertices()[i+0] < minx)
      minx = patr.vertices()[i+0];
    if (patr.vertices()[i+0] > maxx)
      maxx = patr.vertices()[i+0];
    if (patr.vertices()[i+1] < miny)
      miny = patr.vertices()[i+1];
    if (patr.vertices()[i+1] > maxy)
      maxy = patr.vertices()[i+1];
    if (patr.vertices()[i+2] < minz)
      minz = patr.vertices()[i+2];
    if (patr.vertices()[i+2] > maxz)
      maxz = patr.vertices()[i+2];
  }
  escala = 0.3/(maxy-miny); // ejer 2
  centrePatr[0] = (minx+maxx)/2.0; centrePatr[1] = (miny+maxy)/2.0; centrePatr[2] = (minz+maxz)/2.0;
}

void MyGLWidget::modelTransformPatricio ()
{
  TG = glm::translate(TG, suelo);
  TG = glm::scale(TG, glm::vec3(escala, escala, escala));
  TG = glm::translate(TG, -centrePatr);

  glUniformMatrix4fv (transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::creaBuffersPatricio ()
{
  // Carreguem el model de l'OBJ - Atenció! Abans de crear els buffers!
  patr.load("../models/Patricio.obj");

  // Calculem la capsa contenidora del model
  calculaCapsaModel ();

  // Creació del Vertex Array Object del Patricio
  glGenVertexArrays(1, &VAO_Patr);
  glBindVertexArray(VAO_Patr);

  // Creació dels buffers del model patr
  GLuint VBO_Patr[6];
  // Buffer de posicions
  glGenBuffers(6, VBO_Patr);
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Patr[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*patr.faces().size()*3*3, patr.VBO_vertices(), GL_STATIC_DRAW);

  // Activem l'atribut vertexLoc
  glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(vertexLoc);

  // Buffer de normals
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Patr[1]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*patr.faces().size()*3*3, patr.VBO_normals(), GL_STATIC_DRAW);

  glVertexAttribPointer(normalLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(normalLoc);

  // En lloc del color, ara passem tots els paràmetres dels materials
  // Buffer de component ambient
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Patr[2]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*patr.faces().size()*3*3, patr.VBO_matamb(), GL_STATIC_DRAW);

  glVertexAttribPointer(matambLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(matambLoc);

  // Buffer de component difusa
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Patr[3]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*patr.faces().size()*3*3, patr.VBO_matdiff(), GL_STATIC_DRAW);

  glVertexAttribPointer(matdiffLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(matdiffLoc);

  // Buffer de component especular
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Patr[4]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*patr.faces().size()*3*3, patr.VBO_matspec(), GL_STATIC_DRAW);

  glVertexAttribPointer(matspecLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(matspecLoc);

  // Buffer de component shininness
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Patr[5]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*patr.faces().size()*3, patr.VBO_matshin(), GL_STATIC_DRAW);

  glVertexAttribPointer(matshinLoc, 1, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(matshinLoc);

  glBindVertexArray(0);
}

void MyGLWidget::mouseMoveEvent(QMouseEvent *e)
{
  makeCurrent();
  // Aqui cal que es calculi i s'apliqui la rotacio o el zoom com s'escaigui...
  if (DoingInteractive == ROTATE)
  {
    // Fem la rotació
    angleY -= (e->x() - xClick) * M_PI / ample;
    viewTransform ();
  }

  xClick = e->x();
  yClick = e->y();

  update ();
}

void MyGLWidget::keyPressEvent(QKeyEvent* event) {
  makeCurrent();
  switch (event->key()) {
    case Qt::Key_L :
      if (escena) {
        posFocus.x += 0.05;
        glUniform3fv (posFocusLoc, 1, &posFocus[0]);
      }
      break;

    case Qt::Key_K :
      if (escena) {
        posFocus.x -= 0.05;
        glUniform3fv (posFocusLoc, 1, &posFocus[0]);
      }
      break;

    case Qt::Key_1 :
      llum2 = !llum2;
      if (not llum2) colorFocusEsc = glm::vec3(0, 0, 0);
      else colorFocusEsc = glm::vec3(0.8, 0.8, 0.0);
      glUniform3fv (colorFocusLocEsc, 1, &colorFocusEsc[0]);
      break;

    case Qt::Key_2 :
      llum = !llum;
      if (not llum) colorFocus = glm::vec3(0, 0, 0);
      else colorFocus = glm::vec3(0.8, 0.8, 0.8);
      glUniform3fv (colorFocusLoc, 1, &colorFocus[0]);
      break;

    case Qt::Key_B :
      bc = !bc;
      if (bc) glEnable(GL_CULL_FACE);
      else glDisable(GL_CULL_FACE);
      break;

    case Qt::Key_Left :
      if (escena) {
        suelo.x -= 0.2;
        posFocusEsc.x -= 0.2;
        glUniform3fv (posFocusLocEsc, 1, &posFocusEsc[0]);
        modelTransformPatricio();
      }
      break;

    case Qt::Key_Right :
      if (escena) {
        suelo.x += 0.2;
        posFocusEsc.x += 0.2;
        glUniform3fv (posFocusLocEsc, 1, &posFocusEsc[0]);
        modelTransformPatricio();
      }
      break;

    case Qt::Key_Down :
      if (escena) {
        suelo.z -= 0.2;
        posFocusEsc.z -= 0.2;
        glUniform3fv (posFocusLocEsc, 1, &posFocusEsc[0]);
        modelTransformPatricio();
      }
      break;

    case Qt::Key_Up :
      if (escena) {
        suelo.z += 0.2;
        posFocusEsc.z += 0.2;
        glUniform3fv (posFocusLocEsc, 1, &posFocusEsc[0]);
        modelTransformPatricio();
      }
      break;

    case Qt::Key_F :
      escena = !escena;
      glUniform1i (escenaLoc, escena);
      break;



    default: BL3GLWidget::keyPressEvent(event); break;
  }
  update();
}


void MyGLWidget::iniMaterialTerra ()
{
  amb = glm::vec3(0.2,0,0.2);
  diff = glm::vec3(0,0,0.8);
  spec = glm::vec3(0,0,1.0);
  shin = 100;
}

void MyGLWidget::carregaShaders()
{
  BL3GLWidget::carregaShaders();

  posFocusLoc = glGetUniformLocation (program->programId(), "posFocus");
  colorFocusLoc = glGetUniformLocation (program->programId(), "colorFocus");
  posFocusLocEsc = glGetUniformLocation (program->programId(), "posFocusEsc");
  colorFocusLocEsc = glGetUniformLocation (program->programId(), "colorFocusEsc");
  escenaLoc = glGetUniformLocation (program->programId(), "escena");

}


