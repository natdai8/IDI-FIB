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

void MyGLWidget::paintGL ()   // Mètode que has de modificar
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
  if (!cubos)
  {
    glBindVertexArray (VAO_Patr);
    modelTransformPatricio ();
    glDrawArrays(GL_TRIANGLES, 0, patr.faces().size()*3);
  }
  else {
    // Pintem el cub
    glBindVertexArray(VAO_Cub);
    modelTransformCub (2.0, 0.0);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    glBindVertexArray(VAO_Cub);
    modelTransformCub (2.5, 2.*float(M_PI)/3);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    glBindVertexArray(VAO_Cub);
    modelTransformCub (3.0, 4.*float(M_PI)/3);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    glBindVertexArray(0);
  }
}

void MyGLWidget::modelTransformCub (float escala, float angle) 
{
  TG = glm::mat4(1.f);
  TG = glm::rotate(TG, angleCP, glm::vec3(0, 1, 0));
  TG = glm::rotate(TG, angle, glm::vec3(0, 1, 0));
  TG = glm::translate(TG, glm::vec3(5, 0, 0));
  TG = glm::scale(TG, glm::vec3(escala/0.5, escala/0.5, escala/0.5));

  glUniformMatrix4fv (transLoc, 1, GL_FALSE, &TG[0][0]);
  // En aquest mètode has de substituir aquest codi per construir la 
  // transformació geomètrica (TG) del cub usant els paràmetres adientment
}

void MyGLWidget::modelTransformPatricio ()    // Mètode que has de modificar
{
  TG = glm::mat4(1.f);
  TG = glm::rotate(TG, angleCP, glm::vec3(0, 1, 0));
  TG = glm::rotate(TG, angle, glm::vec3(0, 1, 0));
  TG = glm::translate(TG, glm::vec3(5, 0, 0));
  TG = glm::rotate(TG, glm::radians(angle2), glm::vec3(0, 1, 0));
  TG = glm::scale(TG, glm::vec3 (escala*(2.0/1.0), escala*(2.0/1.0), escala*(2.0/1.0)));
  TG = glm::translate(TG, -centreBasePat);

  glUniformMatrix4fv (transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::viewTransform ()    // Mètode que has de modificar
{
  if (!camPlanta) ExamGLWidget::viewTransform();
  else
  {
    View = glm::translate(glm::mat4(1.f), glm::vec3(0, 0, -2*radiEsc));
    View = glm::rotate(View, glm::radians(angleX), glm::vec3(1, 0, 0));
    View = glm::translate(View, -centreEsc);

  glUniformMatrix4fv (viewLoc, 1, GL_FALSE, &View[0][0]);
  }
}

void MyGLWidget::projectTransform ()
{
  if (!camPlanta)
    ExamGLWidget::projectTransform();
  else
  {
    glm::mat4 Proj;  // Matriu de projecció
    Proj = glm::ortho(-radiEsc, radiEsc, -radiEsc, radiEsc, radiEsc, radiEsc*3);

    glUniformMatrix4fv (projLoc, 1, GL_FALSE, &Proj[0][0]);
  }
}

void MyGLWidget::resizeGL (int w, int h)
{
  ExamGLWidget::resizeGL (w, h);
  ra = float(ample)/float(alt);

  if (ra < 1)
  {
    left = -radiEsc;
    right = radiEsc;
    bottom = -radiEsc / ra;
    top = radiEsc / ra;
  }
  else
  {
    left = -radiEsc * ra;
    right = radiEsc * ra;
    bottom = -radiEsc;
    top = radiEsc;
  }
  projectTransform();
}

void MyGLWidget::keyPressEvent(QKeyEvent* event) {
  makeCurrent();
  switch (event->key()) {
  case Qt::Key_V: {
      cubos = !cubos;
    break;
	}
  case Qt::Key_1: {
      angle = 0;
      modelTransformPatricio();
      emit but1();
    break;
	}
  case Qt::Key_2: {
      angle = 2.*float(M_PI)/3;
      modelTransformPatricio();
      emit but2();
    break;
	}
  case Qt::Key_3: {
      angle = 4.*float(M_PI)/3;
      modelTransformPatricio();
      emit but3();
    break;
	}
  case Qt::Key_F: {
      blanc = !blanc;
      if (!blanc) colFoc = glm::vec3(1,1,0);
      else colFoc = glm::vec3(1,1,1);
      glUniform3fv (colfocusLoc, 1, &colFoc[0]);
    break;
	}
  case Qt::Key_C: {
      camPlanta = !camPlanta;
      if (!camPlanta) emit camPers();
      else emit camOrto();
    break;
	}
  case Qt::Key_Right: {
      angleCP += 2.*float(M_PI)/3;
      modelTransformCub(2.0, 0.0);
      modelTransformCub(2.5, 2.*float(M_PI)/3);
      modelTransformCub(3.0, 4.*float(M_PI)/3);
      modelTransformPatricio();
    break;
	}
  case Qt::Key_Left: {
      angleCP -= 2.*float(M_PI)/3;
      modelTransformCub(2.0, 0.0);
      modelTransformCub(2.5, 2.*float(M_PI)/3);
      modelTransformCub(3.0, 4.*float(M_PI)/3);
      modelTransformPatricio();
    break;
	}
  case Qt::Key_R: {
      angle = 0;
      angle2 = -90.f;
      camPlanta = 0;
      angleCP = 0;
      cubos = 1;
      colFoc = glm::vec3(1,1,1);
      glUniform3fv (colfocusLoc, 1, &colFoc[0]);

    break;
	}
  default: ExamGLWidget::keyPressEvent(event); break;
  }
  viewTransform();
  projectTransform();
  update();
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

void MyGLWidget::canvi1()
{
  makeCurrent();
  angle = 0;
  modelTransformPatricio();
  paintGL();
  update();
}

void MyGLWidget::canvi2()
{
  makeCurrent();
  angle = 2.*float(M_PI)/3;
  modelTransformPatricio();
  paintGL();
  update();
}

void MyGLWidget::canvi3()
{
  makeCurrent();
  angle = 4.*float(M_PI)/3;
  modelTransformPatricio();
  paintGL();
  update();
}

