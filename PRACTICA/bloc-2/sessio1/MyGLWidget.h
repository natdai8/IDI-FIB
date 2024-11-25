// MyGLWidget.h
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
