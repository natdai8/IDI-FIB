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

void MyGLWidget::iniEscena ()
{
  creaBuffersPatricio();
  creaBuffersAvio();
  creaBuffersHangar();
  creaBuffersTerra();

  // Paràmetres de l'escena - arbitraris
  glm::vec3 Pmin(0, 0, 0);
  glm::vec3 Pmax(30, 2.5, 24);

  centreEsc = glm::vec3 (Pmin + Pmax)/2.0f;
  radiEsc = glm::distance(Pmin, Pmax)/2.0f;

//   si lookup
  d = 2 * radiEsc;
//   VRP = centre_escena;
//   OBS = VRP + d * glm::vec3(0, 0, 1); // direccio arbitraria e.g en la z
//   UP = glm::vec3(0,1,0);
//
//   angleY = angleX = 0;
}

void MyGLWidget::iniMaterialTerra()
{
  amb = glm::vec3(0.0,0.2,0.2);
  diff = glm::vec3(0.0,0.6,0.6);
  spec = glm::vec3(1,1,1);
  shin = 500;
}

void MyGLWidget::enviaPosFocus()
{
  if (camara == 1)
  {
    posFoc = glm::vec3(0,0,0);
    glUniform3fv (posfocusLoc, 1, &posFoc[0]);
  }
  else
  {
    glm::vec3 posColaAvio = glm::vec3(((capsaAvioMax.x+capsaAvioMin.x)/2),
                                      ((capsaAvioMax.y+capsaAvioMin.y)/2), (capsaAvioMin.z));
    posFoc = glm::vec3(View * TGAvio * glm::vec4(posColaAvio, 1));
    glUniform3fv (posfocusLoc, 1, &posFoc[0]);
  }
}

void MyGLWidget::iniCamera ()
{
  angleY = 0.5;
  angleX = -0.5;
  camera2 = false;
  ra = float(width())/height();

  alfa_inicial = asin(radiEsc/d);
  fov = 2 * alfa_inicial;
  zn = d - radiEsc;
  zf = d + radiEsc;

  projectTransform ();
  viewTransform ();
}

void MyGLWidget::paintGL ()
{
  ExamGLWidget::paintGL();
}

void MyGLWidget::initializeGL ()
{
  // Cal inicialitzar l'ús de les funcions d'OpenGL
  initializeOpenGLFunctions();

  glClearColor(0.5, 0.7, 1.0, 1.0); // defineix color de fons (d'esborrat)
  glEnable(GL_DEPTH_TEST);
  carregaShaders();
  iniEscena ();
  iniCamera ();

  paintGL();
  enviaPosFocus();
}

void MyGLWidget::modelTransformPatricio ()
{
  glm::mat4 TG(1.f);
  TG = glm::translate(TG, glm::vec3 (15.0, 0.0, 12.0));
  TG = glm::rotate(TG, glm::radians(-90.f), glm::vec3(0.0, 1.0, 0.0));
  TG = glm::scale(TG, glm::vec3 (escalaPat*(2.0/1.0), escalaPat*(2.0/1.0), escalaPat*(2.0/1.0)));
  TG = glm::translate(TG, -centreBasePat);

  glUniformMatrix4fv (transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::modelTransformAvio ()
{
  TGAvio = glm::mat4(1.f);
  TGAvio = glm::translate(TGAvio, glm::vec3 (15.0, y, 12.0));
  TGAvio = glm::rotate(TGAvio, glm::radians(float(grauY)), glm::vec3(0, 1, 0));
  TGAvio = glm::translate(TGAvio, glm::vec3 (10.0, 0.0, 0.0));
  TGAvio = glm::scale(TGAvio, glm::vec3 (escalaAvio*(1.5/1.0), escalaAvio*(1.5/1.0), escalaAvio*(1.5/1.0)));
  TGAvio = glm::translate(TGAvio, -centreBaseAvio);

  glUniformMatrix4fv (transLoc, 1, GL_FALSE, &TGAvio[0][0]);
}

void MyGLWidget::viewTransform ()
{
  if (!camera2)
  {
    View = glm::translate(glm::mat4(1.f), glm::vec3(0, 0, -2*radiEsc));
    View = glm::rotate(View, -angleX, glm::vec3(1, 0, 0));
    View = glm::rotate(View, angleY, glm::vec3(0, 1, 0));
    View = glm::translate(View, -centreEsc);

    glUniformMatrix4fv (viewLoc, 1, GL_FALSE, &View[0][0]);
  }
  else
  {
    View = glm::translate(glm::mat4(1.f), glm::vec3(0, -3, 0));
    View = glm::rotate(View, glm::radians(-90.0f), glm::vec3(0, 1, 0));
    View = glm::translate(View, -centreEsc);

    glUniformMatrix4fv (viewLoc, 1, GL_FALSE, &View[0][0]);
  }
}

void MyGLWidget::projectTransform ()
{
  if (!camera2)
  {
    fov = 2 * alfa_inicial;
    zn = d - radiEsc;
    ExamGLWidget::projectTransform();
  }
  else
  {
    fov = 90.0f;
    zn = 0.3;
    ExamGLWidget::projectTransform();
  }
}

void MyGLWidget::keyPressEvent(QKeyEvent* event) 
{
  makeCurrent();
  switch (event->key()) {
  case Qt::Key_Up: {
      if (y < 5) y++;
    break;
	}
  case Qt::Key_Down: {
      if (y > 0) y--;
    break;
	}
  case Qt::Key_Right: {
      grauY -= 11.25;
    break;
	}
  case Qt::Key_F: {
      camara = !camara;
      enviaPosFocus();
    break;
	}
  case Qt::Key_C: {
      camera2 = !camera2;
    break;
	}
  case Qt::Key_R: {
      y = 0;
      camera2 = false;
      angleX = -0.5;
      angleY = 0.5;
      grauY = 0;
      camara = 1;

    break;
	}
  default: ExamGLWidget::keyPressEvent(event); break;
  }
  projectTransform();
  viewTransform();
  update();
}

void MyGLWidget::carregaShaders()
{
  ExamGLWidget::carregaShaders();
  camaraLoc = glGetUniformLocation (program->programId(), "camara");

}


void MyGLWidget::mouseMoveEvent(QMouseEvent *e)
{
  makeCurrent();
  if ((DoingInteractive == ROTATE) && !camera2)
  {
    // Fem la rotació
    angleY += (e->x() - xClick) * M_PI / ample;
    angleX -= (e->y() - yClick) * M_PI / ample;
    viewTransform ();
  }

  xClick = e->x();
  yClick = e->y();

  update ();
}

void MyGLWidget::slider(int y)
{
    makeCurrent();
    if (y < 5) ++y;
    else if (y > 0) --y;
    modelTransformAvio();
    update();
}

void MyGLWidget::canviCamara()
{
    makeCurrent();
    camera2 = !camera2;
    viewTransform();
    projectTransform();
    update();
}

