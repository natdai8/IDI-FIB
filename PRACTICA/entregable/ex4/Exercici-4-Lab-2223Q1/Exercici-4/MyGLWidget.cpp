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
  glEnable(GL_CULL_FACE);

  carregaShaders();

  creaBuffersMorty();
  creaBuffersFantasma();
  creaBuffersTerraIParets();

  iniEscena();
  iniCamera();

  paintGL();
  TGM = TG_morty;
  glUniformMatrix4fv (transLocM, 1, GL_FALSE, &TGM[0][0]);
}

void MyGLWidget::paintGL ()
{
  // En cas de voler canviar els paràmetres del viewport, descomenteu la crida següent i
  // useu els paràmetres que considereu (els que hi ha són els de per defecte)
  // glViewport (0, 0, ample, alt);

  // Esborrem el frame-buffer i el depth-buffer
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // TERRA
  glBindVertexArray (VAO_Terra);
  modelTransformTerra ();
  glDrawArrays(GL_TRIANGLES, 0, 30);

  // MORTY
  glBindVertexArray (VAO_Morty);
  modelTransformMorty ();
  glDrawArrays(GL_TRIANGLES, 0, morty.faces().size()*3);

  // FANTASMA
  if (not llumE and apareix) {
      glBindVertexArray (VAO_Fantasma);
      modelTransformFantasma ();
      glDrawArrays(GL_TRIANGLES, 0, fantasma.faces().size()*3);
  }


  glBindVertexArray(0);
}

void MyGLWidget::iniEscena ()
{
  centreEsc = glm::vec3(5,3,5);
  radiEsc = 8;

  posFocus1 = glm::vec3(0.0, 6.0, 0.0);
  glUniform3fv (posFocusLoc1, 1, &posFocus1[0]);

  posFocus2 = glm::vec3(0.0, 6, 10.0);
  glUniform3fv (posFocusLoc2, 1, &posFocus2[0]);

  posFocus3 = glm::vec3(10.0, 6, 0.0);
  glUniform3fv (posFocusLoc3, 1, &posFocus3[0]);

  posFocus4 = glm::vec3(10.0, 6, 10.0);
  glUniform3fv (posFocusLoc4, 1, &posFocus4[0]);

  colorFocus = glm::vec3(0.7, 0.0, 0.7);
  glUniform3fv (colorFocusLoc, 1, &colorFocus[0]);

  posFocusM = glm::vec3(60.0, -90.0, -7);
  glUniform3fv (posFocusLocM, 1, &posFocusM[0]);

  colorFocusM = glm::vec3(0.9, 0.9, 0.0);
  glUniform3fv (colorFocusLocM, 1, &colorFocusM[0]);
}

void MyGLWidget::modelTransformMorty ()
{
  TG_morty = glm::translate(glm::mat4(1.f), glm::vec3(5,0,5));
  TG_morty = glm::rotate(TG_morty, glm::radians(float(grauM)),glm::vec3(0.f, 1.f, 0.f));
  TG_morty = glm::scale(TG_morty, glm::vec3(escalaMorty, escalaMorty, escalaMorty));
  TG_morty = glm::translate(TG_morty, -centreBaseMorty);

  glUniformMatrix4fv (transLoc, 1, GL_FALSE, &TG_morty[0][0]);
}

void MyGLWidget::modelTransformFantasma ()
{
  glm::mat4 TG;
  TG = glm::translate(glm::mat4(1.f), glm::vec3(1+boox,0.5,5));
  TG = glm::rotate(TG, float(glm::radians(90.0)),glm::vec3(0.f, 1.f, 0.f));
  TG = glm::scale(TG, glm::vec3(escalaFantasma, escalaFantasma, escalaFantasma));
  TG = glm::translate(TG, -centreBaseFantasma);

  glUniformMatrix4fv (transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::projectTransform ()
{
  glm::mat4 Proj;  // Matriu de projecció
  Proj = glm::perspective(float(M_PI/3.0), ra, radiEsc, 3.0f*radiEsc);

  glUniformMatrix4fv (projLoc, 1, GL_FALSE, &Proj[0][0]);
}

void MyGLWidget::viewTransform ()
{
  View = glm::rotate(View, glm::radians(float(grauM)), glm::vec3(0.0, 1.0, 0.0));
  View = glm::translate(glm::mat4(1.f), glm::vec3(0, 0, -2*radiEsc));
  View = glm::rotate(View, -angleY, glm::vec3(0, 1, 0));
  View = glm::translate(View, -centreEsc);

  glUniformMatrix4fv (viewLoc, 1, GL_FALSE, &View[0][0]);
}

void MyGLWidget::mouseMoveEvent(QMouseEvent *e)
{
  makeCurrent();
  // Aqui cal que es calculi i s'apliqui la rotacio o el zoom com s'escaigui...
  if (DoingInteractive == ROTATE)
  {
    // Fem la rotació
    angleY += (e->x() - xClick) * M_PI / ample;
    viewTransform ();
  }

  xClick = e->x();
  yClick = e->y();

  update ();
}

void MyGLWidget::keyPressEvent(QKeyEvent* event) {
  makeCurrent();
  switch (event->key()) {
  case Qt::Key_A: {
      grauM += 45;
      modelTransformMorty();
      TGM = TG_morty;
      glUniformMatrix4fv (transLocM, 1, GL_FALSE, &TGM[0][0]);
      if (grauM % 360 >= 0 and grauM % 360 <= 180) {
          apareix = 1;
          boox += 0.5;
          if (5 - (1+boox) <= 0.5) {
              llumE = 1;
              llumM = 1;
              grauM = 90;
              apareix = 0;
              boox = 0;
              iniEscena();
          }
      }
      else apareix = 0;
    break;
	}
  case Qt::Key_D: {
      grauM -= 45;
      if (grauM == -45) grauM = 315;
      modelTransformMorty();
      TGM = TG_morty;
      glUniformMatrix4fv (transLocM, 1, GL_FALSE, &TGM[0][0]);
      if (grauM % 360 >= 0 and grauM % 360 <= 180) {
          apareix = 1;
          boox += 0.5;
          if (5 - (1+boox) <= 0.5) {
              llumE = 1;
              llumM = 1;
              grauM = 90;
              apareix = 0;
              boox = 0;
              iniEscena();
          }
      }
      else apareix = 0;
    break;
	}
  case Qt::Key_M: {
      llumM = !llumM;
      if (not llumM) {
        colorFocusM = glm::vec3(0, 0, 0);
      }
      else colorFocusM = glm::vec3(0.9, 0.9, 0.0);
      glUniform3fv (colorFocusLocM, 1, &colorFocusM[0]);
    break;
	}
  case Qt::Key_E: {
      llumE = !llumE;
      if (not llumE) {
        colorFocus = glm::vec3(0, 0, 0);
        if (grauM % 360 > 0 and grauM % 360 < 180) apareix = 1;
      }
      else {
        colorFocus = glm::vec3(0.7, 0.0, 0.7);
        if (grauM % 360 > 0 and grauM % 360 < 180) apareix = 0;
      }
      glUniform3fv (colorFocusLoc, 1, &colorFocus[0]);
    break;
	}	
  default: LL4GLWidget::keyPressEvent(event); break;
  }
  projectTransform();
  viewTransform();
  update();

}

void MyGLWidget::carregaShaders()
{
  LL4GLWidget::carregaShaders();

  posFocusLoc1 = glGetUniformLocation (program->programId(), "posFocus1");
  posFocusLoc2 = glGetUniformLocation (program->programId(), "posFocus2");
  posFocusLoc3 = glGetUniformLocation (program->programId(), "posFocus3");
  posFocusLoc4 = glGetUniformLocation (program->programId(), "posFocus4");
  colorFocusLoc = glGetUniformLocation (program->programId(), "colorFocus");

  posFocusLocM = glGetUniformLocation (program->programId(), "posFocusM");
  colorFocusLocM = glGetUniformLocation (program->programId(), "colorFocusM");
  transLocM = glGetUniformLocation (program->programId(), "TGM");

}
