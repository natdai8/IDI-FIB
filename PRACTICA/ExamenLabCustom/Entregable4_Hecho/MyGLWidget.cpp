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

void MyGLWidget::reset() {
  rotMorty = 0;
  posFantasma = glm::vec3(0.0,0.0,0.0);
  colFocus1 = colFocus2 = colFocus3 = colFocus4 = glm::vec3(0.7,0.0,0.7);
  glUniform3fv(colFocus1Loc, 1, &colFocus1[0]);
  glUniform3fv(colFocus2Loc, 1, &colFocus2[0]);
  glUniform3fv(colFocus3Loc, 1, &colFocus3[0]);
  glUniform3fv(colFocus4Loc, 1, &colFocus4[0]);
  colFocusLinterna = glm::vec3(0.9,0.9,0.0);
  glUniform3fv(colFocusLinternaLoc, 1, &colFocusLinterna[0]);

  f = 1;
  g = 1;
  n = 1;
  alturaM = 2;
  altura = 0;
  grauF = 0;
  pers = 1;

  emit actualizar(0);
  emit actCamaraP();
  iniCamera();
  iniEscena();
}

void MyGLWidget::initializeGL ()
{
  // Cal inicialitzar l'ús de les funcions d'OpenGL
  initializeOpenGLFunctions();  

  glClearColor(0.5, 0.7, 1.0, 1.0); // defineix color de fons (d'esborrat)
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  
  carregaShaders();
  carregaShaders_nuevos();
  
  creaBuffersMorty();
  creaBuffersFantasma();
  creaBuffersTerraIParets();
  
  //Colors dels focus
  colFocus1 = colFocus2 = colFocus3 = colFocus4 = glm::vec3(0.7,0.0,0.7);
  glUniform3fv(colFocus1Loc, 1, &colFocus1[0]);
  glUniform3fv(colFocus2Loc, 1, &colFocus2[0]);
  glUniform3fv(colFocus3Loc, 1, &colFocus3[0]);
  glUniform3fv(colFocus4Loc, 1, &colFocus4[0]);
  
  colFocusLinterna = glm::vec3(0.9,0.9,0.0);
  glUniform3fv(colFocusLinternaLoc, 1, &colFocusLinterna[0]);
  
  //pos dels focus en SCA
  posFocus1 = glm::vec3(0.0,6.0,0.0);
  glUniform3fv(posFocus1Loc, 1, &posFocus1[0]);
      
  posFocus2 = glm::vec3(10.0,6.0,0.0);
  glUniform3fv(posFocus2Loc, 1, &posFocus2[0]);
  
  posFocus3 = glm::vec3(10.0,6.0,10.0);
  glUniform3fv(posFocus3Loc, 1, &posFocus3[0]);
  
  posFocus4 = glm::vec3(0.0,6.0,10.0);
  glUniform3fv(posFocus4Loc, 1, &posFocus4[0]);
  
  //pos del focus en SCM
  posFocusLinterna = glm::vec3(60.0,-90.0,-7.0);
  glUniform3fv(posFocusLinternaLoc, 1, &posFocusLinterna[0]);

  colFocusAzul = glm::vec3(0.0,0.0,1.0);
  glUniform3fv(colFocusAzulLoc, 1, &colFocusAzul[0]);
  posFocusAzul = glm::vec3(2.0, 2.0, 2.0);
  glUniform3fv(posFocusAzulLoc, 1, &posFocusAzul[0]);

  colFocusBlanco = glm::vec3(1.0,1.0,1.0);
  glUniform3fv(colFocusBlancoLoc, 1, &colFocusBlanco[0]);
  posFocusBlanco = glm::vec3(0, 0, 0);
  glUniform3fv(posFocusBlancoLoc, 1, &posFocusBlanco[0]);
  
  iniEscena();
  iniCamera();
  
  paintGL();
  
  TGLinterna = TG_morty;
  glUniformMatrix4fv (TGLinternaLoc, 1, GL_FALSE, &TGLinterna[0][0]);
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
  if (n)
  {
    glBindVertexArray (VAO_Morty);
    modelTransformMorty ();
    glDrawArrays(GL_TRIANGLES, 0, morty.faces().size()*3);
  }
  // FANTASMA
  //Solo se pinta si están los focos de la escena apagados y el morty no le está mirando
  if (colFocus1 == glm::vec3(0.0,0.0,0.0) and rotMorty % 8 != 3 and rotMorty % 8 != 4 and rotMorty % 8 != 5) {
    glBindVertexArray (VAO_Fantasma);
    modelTransformFantasma ();
    glDrawArrays(GL_TRIANGLES, 0, fantasma.faces().size()*3);
  }

  
  glBindVertexArray(0);
}

void MyGLWidget::modelTransformMorty ()
{
  TG_morty = glm::translate(glm::mat4(1.f), glm::vec3(5,0,5));
  TG_morty = glm::rotate(TG_morty, float(glm::radians(90.0 + 45.0*rotMorty)),glm::vec3(0.f, 1.f, 0.f));
  TG_morty = glm::scale(TG_morty, glm::vec3(escalaMorty, escalaMorty*(alturaM/2.5), escalaMorty));
  TG_morty = glm::translate(TG_morty, -centreBaseMorty);
  
  glUniformMatrix4fv (transLoc, 1, GL_FALSE, &TG_morty[0][0]);
}

void MyGLWidget::modelTransformFantasma ()
{
  glm::mat4 TG(1.f);
  TG = glm::translate(TG, glm::vec3(5, 0.5+altura, 5));
  TG = glm::rotate(TG, float(glm::radians(grauF)),glm::vec3(0.f, 1.f, 0.f));
  TG = glm::translate(TG, glm::vec3(-4,0,0)-posFantasma);
  TG = glm::rotate(TG, float(glm::radians(90.0)),glm::vec3(0.f, 1.f, 0.f));
  TG = glm::scale(TG, glm::vec3(escalaFantasma, escalaFantasma, escalaFantasma));
  TG = glm::translate(TG, -centreBaseFantasma);
  
  glUniformMatrix4fv (transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::projectTransform ()
{
  if (pers)
  {
    glm::mat4 Proj;  // Matriu de projecció
    if (cam == 4) Proj = glm::perspective(float(M_PI/3.0), ra, radiEsc, 3.0f*radiEsc);
    else if (cam == 3) Proj = glm::perspective(float(M_PI/3.0), ra, 0.3f, 3.0f*radiEsc);
    glUniformMatrix4fv (projLoc, 1, GL_FALSE, &Proj[0][0]);
  }
  else
  {
    glm::mat4 Proj;  // Matriu de projecció
    Proj = glm::ortho(-radiEsc, radiEsc, -radiEsc, radiEsc, radiEsc, 3.0f*radiEsc);

    glUniformMatrix4fv (projLoc, 1, GL_FALSE, &Proj[0][0]);
  }
}

void MyGLWidget::viewTransform ()
{
  if (cam == 4)
  {
    View = glm::translate(glm::mat4(1.f), glm::vec3(0, 0, -2*radiEsc));
    View = glm::rotate(View, -angleY, glm::vec3(0, 1, 0));
    View = glm::translate(View, -centreEsc);

    glUniformMatrix4fv (viewLoc, 1, GL_FALSE, &View[0][0]);
  }
  else if (cam == 3)
  {
    View = glm::lookAt(glm::vec3(1,1,1), glm::vec3(9,1,9), glm::vec3(0,0,1));

    glUniformMatrix4fv (viewLoc, 1, GL_FALSE, &View[0][0]);
  }
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
  case Qt::Key_A: {
      //Paso 1: Girar Morty
      ++rotMorty;
      modelTransformMorty();
      TGLinterna = TG_morty;
      glUniformMatrix4fv (TGLinternaLoc, 1, GL_FALSE, &TGLinterna[0][0]);

     // vrpMorty =
      
      //Paso 2: Mover Fantasma
      if (rotMorty % 8 != 3 and rotMorty % 8 != 4 and rotMorty % 8 != 5) {
        posFantasma.x += 0.5;
        modelTransformFantasma();
      }
      
      //Paso 3: Check de reset
      if (glm::distance(glm::vec3(1,0.5,5) + posFantasma, glm::vec3(5.0,0.5,5.0)) <= 0.5) {
        reset();
      }
      emit actualizar(rotMorty);

    break;
	}
  case Qt::Key_D: {
      //Paso 1: Girar Morty
      --rotMorty;
      if (rotMorty < 0) rotMorty = 7;
      modelTransformMorty();
      TGLinterna = TG_morty;
      glUniformMatrix4fv (TGLinternaLoc, 1, GL_FALSE, &TGLinterna[0][0]);
      
      //Paso 2: Mover Fantasma
      if (rotMorty % 8 != 3 and rotMorty % 8 != 4 and rotMorty % 8 != 5) {
        posFantasma.x += 0.5;
        modelTransformFantasma();
      }
      
      //Paso 3: Check de reset
      if (glm::distance(glm::vec3(1,0.5,5) + posFantasma, glm::vec3(5.0,0.5,5.0)) <= 0.5) {
        reset();
      }
      emit actualizar(rotMorty);

    break;
	}
  case Qt::Key_M: {
      //Enciendan focos
      if (colFocus1 == glm::vec3(0.0,0.0,0.0)){
        colFocus1 = colFocus2 = colFocus3 = colFocus4 = glm::vec3(0.7,0.0,0.7);
        glUniform3fv(colFocus1Loc, 1, &colFocus1[0]);
        glUniform3fv(colFocus2Loc, 1, &colFocus2[0]);
        glUniform3fv(colFocus3Loc, 1, &colFocus3[0]);
        glUniform3fv(colFocus4Loc, 1, &colFocus4[0]);
      }
      //Apaguen focos
      else if (colFocus1 == glm::vec3(0.7,0.0,0.7)) {
        colFocus1 = colFocus2 = colFocus3 = colFocus4 = glm::vec3(0.0,0.0,0.0);
        glUniform3fv(colFocus1Loc, 1, &colFocus1[0]);
        glUniform3fv(colFocus2Loc, 1, &colFocus2[0]);
        glUniform3fv(colFocus3Loc, 1, &colFocus3[0]);
        glUniform3fv(colFocus4Loc, 1, &colFocus4[0]);
      }
    break;
	}
  case Qt::Key_E: {
      //Enciendan Linterna
      if (colFocusLinterna == glm::vec3(0.0,0.0,0.0)) {
        colFocusLinterna = glm::vec3(0.9,0.9,0.0);
        glUniform3fv(colFocusLinternaLoc, 1, &colFocusLinterna[0]);

      }
      else if (colFocusLinterna == glm::vec3(0.9,0.9,0.0)) {
        colFocusLinterna = glm::vec3(0.0,0.0,0.0);
        glUniform3fv(colFocusLinternaLoc, 1, &colFocusLinterna[0]);

      }
    break;
	}
  case Qt::Key_G: {
    g = !g;
    if (g) glEnable(GL_CULL_FACE);
    else glDisable(GL_CULL_FACE);
    break;
  }
  case Qt::Key_F: {
    f = !f;
    if (f) glEnable(GL_DEPTH_TEST);
    else glDisable(GL_DEPTH_TEST);
    break;
  }
  case Qt::Key_N: {
    n = !n;
    break;
  }
  case Qt::Key_Z: {
    grauF -= 45;
    break;
  }
  case Qt::Key_C: {
    grauF += 45;
    break;
  }
  case Qt::Key_W: {
    altura += 0.5;
    break;
  }
  case Qt::Key_S: {
    altura -= 0.5;
    break;
  }
  case Qt::Key_Y: {
    alturaM += 1.0;
    break;
  }
  case Qt::Key_H: {
    alturaM -= 1.0;
    break;
  }
  case Qt::Key_P: {
    pers = 1;
    emit actCamaraP();
    break;
  }
  case Qt::Key_O: {
    pers = 0;
    emit actCamaraO();
    break;
  }
  case Qt::Key_3: {
    cam = 3;
    break;
  }
  case Qt::Key_4: {
    cam = 4;
    zn = radiEsc;
    zf = 3.f*radiEsc;
    break;
  }
  case Qt::Key_B: {
    if (colFocusAzul == glm::vec3(0,0,1)) colFocusAzul = glm::vec3(0,0,0);
    else colFocusAzul = glm::vec3(0,0,1);
    glUniform3fv(colFocusAzulLoc, 1, &colFocusAzul[0]);

    break;
  }
  case Qt::Key_I: {
    if (colFocusBlanco == glm::vec3(1,1,1)) colFocusBlanco = glm::vec3(0,0,0);
    else colFocusBlanco = glm::vec3(1,1,1);
    glUniform3fv(colFocusBlancoLoc, 1, &colFocusBlanco[0]);

    break;
  }
  case Qt::Key_R: {
    reset();
    break;
  }
  default: LL4GLWidget::keyPressEvent(event); break;
  }
  viewTransform();
   projectTransform();
  update();
}

void MyGLWidget::carregaShaders_nuevos() {
  
    posFocus1Loc = glGetUniformLocation (program->programId(), "posFocus1");
    colFocus1Loc = glGetUniformLocation (program->programId(), "colorFocus1");
    
    posFocus2Loc = glGetUniformLocation (program->programId(), "posFocus2");
    colFocus2Loc = glGetUniformLocation (program->programId(), "colorFocus2");
    
    posFocus3Loc = glGetUniformLocation (program->programId(), "posFocus3");
    colFocus3Loc = glGetUniformLocation (program->programId(), "colorFocus3");
    
    posFocus4Loc = glGetUniformLocation (program->programId(), "posFocus4");
    colFocus4Loc = glGetUniformLocation (program->programId(), "colorFocus4");
    
    posFocusLinternaLoc = glGetUniformLocation (program->programId(), "posFocusLinterna");
    colFocusLinternaLoc = glGetUniformLocation (program->programId(), "colorFocusLinterna");
    
    TGLinternaLoc = glGetUniformLocation (program->programId(), "TGLint");

    posFocusAzulLoc = glGetUniformLocation (program->programId(), "posFocusAzul");
    colFocusAzulLoc = glGetUniformLocation (program->programId(), "colorFocusAzul");

    posFocusBlancoLoc = glGetUniformLocation (program->programId(), "posFocusBlanco");
    colFocusBlancoLoc = glGetUniformLocation (program->programId(), "colorFocusBlanco");
}

void MyGLWidget::rotarMorty (int grau)
{
    makeCurrent();
    rotMorty = grau;
    viewTransform();
    projectTransform();
    update();
}

void MyGLWidget::canviO ()
{
    makeCurrent();
    pers = false;
    viewTransform();
    projectTransform();
    update();
}

void MyGLWidget::canviP ()
{
    makeCurrent();
    pers = true;
    viewTransform();
    projectTransform();
    update();
}






