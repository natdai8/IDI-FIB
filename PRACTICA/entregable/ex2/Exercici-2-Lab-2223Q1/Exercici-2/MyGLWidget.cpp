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

MyGLWidget::~MyGLWidget() {}

void MyGLWidget::paintGL ()
{
    // descomentar per canviar paràmetres
    // glViewport (0, 0, ample, alt);

    // Esborrem el frame-buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Rick
    glBindVertexArray (VAO_models[RICK]);
    RickTransform();
    glDrawArrays(GL_TRIANGLES, 0, models[RICK].faces().size()*3);

    // Morty
    funcionPortal(posMorty);

    glBindVertexArray (VAO_models[MORTY]);
    if (evilmorty) // primera vez que pasa
    {
        MortyVermellTransform();
        glUniform1i(mortyLoc, 0);
        glDrawArrays(GL_TRIANGLES, 0, models[MORTY].faces().size()*3);
    }
    MortyTransform();
    glUniform1i(mortyLoc, 1);
    glDrawArrays(GL_TRIANGLES, 0, models[MORTY].faces().size()*3);

    // Portal
    if (portal == 1) {
        glBindVertexArray (VAO_models[PORTAL]);
        PortalTransform();
        glDrawArrays(GL_TRIANGLES, 0, models[PORTAL].faces().size()*3);
    }
    // Terra
    glBindVertexArray (VAO_Terra);
    identTransform();
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    glBindVertexArray (0);
}

void MyGLWidget::RickTransform()
{
    glm::mat4 TG(1.0f);
    TG = glm::translate(TG, glm::vec3(-2.5, 0, 0));
    TG = glm::rotate(TG, glm::radians(float(grauY)), glm::vec3(0, 1, 0));
    TG = glm::rotate(TG, float(M_PI), glm::vec3(0, 1, 0));
    TG = glm::scale(TG, glm::vec3(escalaModels[RICK]));
    TG = glm::translate(TG, -centreBaseModels[RICK]);
    glUniformMatrix4fv(transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::MortyTransform ()
{
    glm::mat4 TG(1.0f);
    TG = glm::translate(TG, posMorty);
    TG = glm::rotate(TG, glm::radians(float(grauM)), glm::vec3(0, 1, 0));
    TG = glm::scale(TG, glm::vec3(escalaModels[MORTY]));
    TG = glm::translate(TG, -centreBaseModels[MORTY]);
    TGMorty = TG;
    glUniformMatrix4fv(transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::MortyVermellTransform ()
{
    glm::mat4 TG(1.0f);
    TG = glm::translate(TG, glm::vec3(-2.5, 0, 0));
    TG = glm::rotate(TG, glm::radians(float(grauEM)), glm::vec3(0, 1, 0));
    TG = glm::translate(TG, glm::vec3(0, 0,-3));
    TG = glm::rotate(TG, glm::radians(float(grauJ)), glm::vec3(0, 1, 0));
    TG = glm::scale(TG, glm::vec3(escalaModels[MORTY]));
    TG = glm::translate(TG, -centreBaseModels[MORTY]);
    TGMorty = TG;
    glUniformMatrix4fv(transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::PortalTransform()
{
    glm::mat4 TG(1.0f);
    TG = glm::translate(TG, glm::vec3(-2.5, 0, 0));
    TG = glm::rotate(TG, glm::radians(float(grauYP)), glm::vec3(0, 1, 0));
    TG = glm::translate(TG, glm::vec3(0, 0,-3));
    TG = glm::scale(TG, glm::vec3((escalaModels[PORTAL]/4)/escalaModels[PORTAL], escalaModels[PORTAL], escalaModels[PORTAL])); // (escalaModels[PORTAL]/4)/escalaModels[PORTAL] -> 0.25
    TG = glm::translate(TG, -centreBaseModels[PORTAL]);
    glUniformMatrix4fv(transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::iniCamera()
{
    radiEscena = sqrt((7.5*7.5)+(5*5)+(1.5*1.5));
    d = 2 * radiEscena;
    centreEscena = glm::vec3(0,1.5,0);

    alfa_inicial = asin(radiEscena/d);
    fov = 2 * alfa_inicial;
    ra = 1.0f;
    znear = d - radiEscena;
    zfar  = d + radiEscena;
    projectTransform();

    factorAngleX = glm::radians(45.);
    viewTransform();
}

void MyGLWidget::carregaShaders()
{
    LL2GLWidget::carregaShaders();
    mortyLoc = glGetUniformLocation (program->programId(), "mortyNormal");
}

bool MyGLWidget::MortyPortalTest(float angleRick, glm::vec3 posMorty)
{
  glm::vec3 posPortal = glm::vec3(sin(angleRick),0.0,cos(angleRick))*glm::vec3(-3) + glm::vec3(-2.5,0,0);
  return (glm::distance(posMorty,posPortal) <= 0.2f);
}

void MyGLWidget::funcionPortal(glm::vec3 posMorty)
{
    if (MortyPortalTest(glm::radians(float(grauYP)), posMorty)) {
        evilmorty = true;
        portal = 0;
        grauEM = grauYP;
        grauJ = grauM;
    }

}

void MyGLWidget::viewTransform() // angles d'euler
{
    glm::mat4 View(1.0);

    if (pov == 1) {
        View = glm::translate(View, glm::vec3(0.0, -0.8, 0));
        View = glm::rotate(View, glm::radians(float(-grauM)), glm::vec3(0.0, 1.0, 0.0));
        View = glm::rotate(View, glm::radians(180.f), glm::vec3(0.0,1.0,0.0));
        View = glm::translate(View, -posMorty);
        glUniformMatrix4fv (viewLoc, 1, GL_FALSE, &View[0][0]);
    }
    else {
        View = glm::translate(View, glm::vec3(0.0, 0.0, -d));
        View = glm::rotate(View, factorAngleX, glm::vec3(1.0, 0.0, 0.0));
        View = glm::rotate(View, -factorAngleY, glm::vec3(0.0, 1.0, 0.0));
        View = glm::translate(View, -centreEscena);
        glUniformMatrix4fv (viewLoc, 1, GL_FALSE, &View[0][0]);
    }
}

void MyGLWidget::projectTransform()
{
    glm::mat4 Proj(1.0f);

    if (pov == 1) znear = 0.25;
    else znear = d - radiEscena;

    Proj = glm::perspective (fov, ra, znear, zfar);
    glUniformMatrix4fv (projLoc, 1, GL_FALSE, &Proj[0][0]);
}

void MyGLWidget::mouseMoveEvent(QMouseEvent *e)
{
    makeCurrent();

    if (e->x() > xClick) factorAngleY -= 0.05;
    else if (e->x() < xClick) factorAngleY += 0.05;

    if (e->y() > yClick) factorAngleX += 0.05;
    else if (e->y() < yClick) factorAngleX -= 0.05;

    xClick = e->x();
    yClick = e->y();

    viewTransform();
    update ();
}

void MyGLWidget::keyPressEvent(QKeyEvent* event)
{
    makeCurrent();
    switch (event->key()) {

    case Qt::Key_Up: {
    	if (grauM % 360 == 0) posMorty += glm::vec3(0.0,0.0,0.1);
        else if (grauM % 360 == 45) posMorty += glm::vec3(0.1,0.0,0.1);
        else if (grauM % 360 == 90) posMorty += glm::vec3(0.1,0.0,0.0);
        else if (grauM % 360 == 135) posMorty += glm::vec3(0.1,0.0,-0.1);
        else if (grauM % 360 == 180) posMorty += glm::vec3(0.0,0.0,-0.1);
        else if (grauM % 360 == 225) posMorty += glm::vec3(-0.1,0.0,-0.1);
        else if (grauM % 360 == 270) posMorty += glm::vec3(-0.1,0.0,0.0);
        else if (grauM % 360 == 315) posMorty += glm::vec3(-0.1,0.0,0.1);

        if (pov == 1) {
            viewTransform();
            projectTransform();
        }
        break;
    }
    case Qt::Key_Down: {
        if (grauM % 360 == 0) posMorty -= glm::vec3(0.0,0.0,0.1);
        else if (grauM % 360 == 45) posMorty -= glm::vec3(0.1,0.0,0.1);
        else if (grauM % 360 == 90) posMorty -= glm::vec3(0.1,0.0,0.0);
        else if (grauM % 360 == 135) posMorty -= glm::vec3(0.1,0.0,-0.1);
        else if (grauM % 360 == 180) posMorty -= glm::vec3(0.0,0.0,-0.1);
        else if (grauM % 360 == 225) posMorty -= glm::vec3(-0.1,0.0,-0.1);
        else if (grauM % 360 == 270) posMorty -= glm::vec3(-0.1,0.0,0.0);
        else if (grauM % 360 == 315) posMorty -= glm::vec3(-0.1,0.0,0.1);

        if (pov == 1) {
            viewTransform();
            projectTransform();
        }
        break;
    }
    case Qt::Key_Q: {
        grauY += 45;
        break;
    }
    case Qt::Key_E: {
        grauY -= 45;
        break;
    }
    case Qt::Key_P: {
        if (grauYP % 360 == grauY % 360) portal = !portal;
        else {
            grauYP = grauY;
            portal = 1;
        }
        break;
    }
    case Qt::Key_Left: {
        grauM += 45;
        if (pov == 1) {
            viewTransform();
            projectTransform();
        }
        break;
    }
    case Qt::Key_Right: {
        grauM -= 45;
        if (grauM < 0) grauM = 315;
        if (pov == 1) {
            viewTransform();
            projectTransform();
        }
        break;
    }
    case Qt::Key_C: {
        pov = !pov;
        factorAngleX = float(M_PI/4);
        factorAngleY = 0;
        viewTransform();
        projectTransform();
        break;
    }
     case Qt::Key_R: {
        portal = 1;
        grauY = 0;
        grauYP = 0;
        factorAngleX = float(M_PI/4);
        factorAngleY = 0;
        pov = 0;
        grauM = 0;
        posMorty = glm::vec3(1, 0, 0);
        evilmorty = false;
        grauEM = 0;
        grauJ = 0;
        viewTransform();
        projectTransform();
        break;
    }
    default: event->ignore(); break;
  }

  update();
}



