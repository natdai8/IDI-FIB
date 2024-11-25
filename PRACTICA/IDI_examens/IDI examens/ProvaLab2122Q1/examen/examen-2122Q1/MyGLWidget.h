#include "ExamGLWidget.h"

class MyGLWidget:public ExamGLWidget
{
  Q_OBJECT

  public:
    MyGLWidget(QWidget *parent=0) : ExamGLWidget(parent) {}
    ~MyGLWidget();

  protected:
    virtual void paintGL ();
    virtual void keyPressEvent(QKeyEvent* event);
    virtual void mouseMoveEvent (QMouseEvent *event);

    virtual void modelTransformPatricio ();
    virtual void modelTransformAvio ();
    virtual void iniEscena ();
    virtual void iniCamera ();
    virtual void projectTransform ();
    virtual void viewTransform ();
    virtual void enviaPosFocus ();
    virtual void iniMaterialTerra ();
    virtual void carregaShaders();
    virtual void initializeGL();

    float d = 0, alfa_inicial = 0, grauY = 0, y = 0;
    glm::vec3 Pmin, Pmax;

    int camara = 1;
    GLuint camaraLoc;

  private:
    int printOglError(const char file[], int line, const char func[]);

  public slots:
    void slider(int y);
    void canviCamara();
};
