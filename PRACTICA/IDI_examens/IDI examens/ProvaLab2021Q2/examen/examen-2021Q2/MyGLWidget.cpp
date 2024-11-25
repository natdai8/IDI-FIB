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
  creaBuffersTerra();
  creaBuffersCub();
  creaBuffersEsfera();

  glm::vec3 Pmax(30, 4, 20);
  glm::vec3 Pmin(0, 0, 0);

  centreEsc = glm::vec3(Pmax+Pmin)/2.0f; //vrp
  radiEsc = glm::distance(Pmax, Pmin)/2.0f;
  d = 2 * radiEsc;

  enviaPosFocus();
}

void MyGLWidget::enviaPosFocus()
{
  if (camara) posFoc = glm::vec3(0,0,0);
  else posFoc = glm::vec3(15,10,10);

  glUniform3fv (posfocusLoc, 1, &posFoc[0]);
}

void MyGLWidget::iniCamera ()
{
  angleY = 0.5;
  angleX = -0.5;
  camPlanta = false;
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
// En cas de voler canviar els paràmetres del viewport, descomenteu la crida següent i
// useu els paràmetres que considereu (els que hi ha són els de per defecte)
//  glViewport (0, 0, ample, alt);

  // Esborrem el frame-buffer i el depth-buffer
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Pintem el terra
  glBindVertexArray (VAO_Terra);
  modelTransformTerra ();
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

  // Pintem el Patricio
  glBindVertexArray (VAO_Patr);
  modelTransformPatricio ();
  glDrawArrays(GL_TRIANGLES, 0, patr.faces().size()*3);

  // Pintem l'arbre
  pintaArbre (glm::vec3(10,0,10));
  pintaArbre (glm::vec3(20,0,5));
  pintaArbre (glm::vec3(25,0,15));

  glBindVertexArray(0);
}

void MyGLWidget::modelTransformPatricio ()
{
  TG = glm::mat4(1.f);
  TG = glm::translate(TG, glm::vec3(10, 0, 10));
  TG = glm::rotate(TG, glm::radians(float(grauP)), glm::vec3(0, 1, 0));
  TG = glm::translate(TG, glm::vec3(5, 0, 0));
  TG = glm::scale(TG, glm::vec3 (escala*(2/1), escala*(2/1), escala*(2/1)));
  TG = glm::translate(TG, -centreBasePat);

  glUniformMatrix4fv (transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::viewTransform ()
{
  if (!camPlanta)
  {
    View = glm::translate(glm::mat4(1.f), glm::vec3(0, 0, -2*radiEsc));
    View = glm::rotate(View, -angleX, glm::vec3(1, 0, 0));
    View = glm::rotate(View, angleY, glm::vec3(0, 1, 0));
    View = glm::translate(View, -centreEsc);

    glUniformMatrix4fv (viewLoc, 1, GL_FALSE, &View[0][0]);
  }
  else
  {
    View = glm::translate(glm::mat4(1.f), glm::vec3(0, 0, -2*radiEsc));
    View = glm::rotate(View, glm::radians(90.f), glm::vec3(1, 0, 0));
    View = glm::translate(View, -centreEsc);

    glUniformMatrix4fv (viewLoc, 1, GL_FALSE, &View[0][0]);
  }
}

void MyGLWidget::projectTransform ()
{
  if (!camPlanta)
  {
    glm::mat4 Proj;  // Matriu de projecció
    Proj = glm::perspective(fov, ra, zn, zf);

    glUniformMatrix4fv (projLoc, 1, GL_FALSE, &Proj[0][0]);
  }
  else
  {
    glm::mat4 Proj;  // Matriu de projecció
    Proj = glm::ortho(-radiEsc, radiEsc, -radiEsc, radiEsc, zn, zf);

    glUniformMatrix4fv (projLoc, 1, GL_FALSE, &Proj[0][0]);
  }
}

void MyGLWidget::keyPressEvent(QKeyEvent* event) 
{
  makeCurrent();
  switch (event->key()) {
  case Qt::Key_Up: {
      grauP -= 11.25;
      emit girPatricio();
    break;
	}
  case Qt::Key_F: {
      camara = !camara;
      enviaPosFocus();
    break;
	}
  case Qt::Key_C: {
      camPlanta = !camPlanta;
      if (camPlanta) emit camOrto();
      else emit camPers();
    break;
	}
  case Qt::Key_R: {
      camPlanta = 0;
      grauP = 0;
      camara = 1;
      angleX = -0.5;
      angleY = 0.5;
    break;
	}
  default: ExamGLWidget::keyPressEvent(event); break;
  }
  enviaPosFocus();
  viewTransform();
  projectTransform();
  update();
}

void MyGLWidget::mouseMoveEvent(QMouseEvent *e)
{
  makeCurrent();
  if ((DoingInteractive == ROTATE) && !camPlanta)
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

void MyGLWidget::canviCamaraP()
{
  makeCurrent();
  camPlanta = false;
  viewTransform();
  projectTransform();
  update();
}

void MyGLWidget::canviCamaraO()
{
  makeCurrent();
  camPlanta = true;
  viewTransform();
  projectTransform();
  update();
}

void MyGLWidget::girP()
{
  makeCurrent();
  grauP -= 11.25;
  viewTransform();
  projectTransform();
  update();
}
