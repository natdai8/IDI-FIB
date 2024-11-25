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
    BL2GLWidget::initializeGL();
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
    BL2GLWidget::paintGL();
    projectTransform();
    viewTransform();
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
    OBS = glm::vec3(0,0,1);
    VRP = glm::vec3(0,0,0);
    UP = glm::vec3(1,0,0);
    viewTransform();

    FOV = float(M_PI)/2.0f;
    ra = 1.0f;
    znear = 0.4f;
    zfar = 3.0f;
    projectTransform();
}

// .h
  /*
   * GLuint projLoc;
     glm::vec3 OBS, VRP, UP;
     float FOV, ra, znear, zfar;

    protected:
        virtual void carregaShaders ();
        virtual void projectTransform ();
        virtual void paintGL ();
        virtual void viewTransform();
        virtual void initializeGL ();
        virtual void ini_camera();
  */

// vertex shader

  /*
    uniform mat4 proj;
    uniform mat4 view;
    gl_Position = proj * view * TG * vec4 (vertex, 1.0);
  */
