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
    GLuint VAO_Patricio, VAO_Terra;

    float rad = 1;

    glm::vec3 centre_escena, centre_model;
    float radi, d , alfa_inicial, alfa_nou = 0;

    float xmin, xmax, ymin, ymax, zmin, zmax, alturaM = 0;

    bool ortogonal = false;
    float left, right, bottom, top = 0;

    float angleY, angleX = 0;
    float xant, yant = 0;

  protected:

    virtual void carregaShaders ();
    virtual void projectTransform ();
    virtual void projectTransformOrtogonal ();
    virtual void paintGL ();
    virtual void viewTransform ();

    virtual void initializeGL ();
    virtual void ini_camera ();

    virtual void creaBuffers();

    virtual void modelTransformPatricioCentre();
    virtual void modelTransformPatricioDalt();
    virtual void modelTransformPatricioBaix();

    virtual void keyPressEvent (QKeyEvent *event);
    virtual void mouseMoveEvent (QMouseEvent* e);
    virtual void modelTransform2 ();

    virtual void resizeGL (int w, int h);
    virtual void capsa_contenidora_model();
};
