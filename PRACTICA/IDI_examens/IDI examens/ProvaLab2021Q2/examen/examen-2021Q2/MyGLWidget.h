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
    virtual void enviaPosFocus ();
    virtual void iniEscena ();
    virtual void iniCamera ();
    virtual void projectTransform ();
    virtual void viewTransform ();

    float d = 0, alfa_inicial = 0, grauP = 0;
    int camara = 1;

  private:
    int printOglError(const char file[], int line, const char func[]);

  public slots:
    void canviCamaraP();
    void canviCamaraO();
    void girP();

  signals:
    void camPers();
    void camOrto();
    void girPatricio();
};
