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
    virtual void modelTransformCub (float escala, float angle);
    virtual void modelTransformPatricio ();
    virtual void projectTransform ();
    virtual void viewTransform ();

    virtual void resizeGL (int w, int h);

    float angle = 0, angle2 = -90.f, angleCP = 0;
    int cubos = 1, blanc = 1;
    float angleY = 90.f, angleX = 90.f;
    float left, right, bottom, top;
    float zn = 2, zf = 50;

  private:
    int printOglError(const char file[], int line, const char func[]);

  public slots:
    void canviCamaraP();
    void canviCamaraO();
    void canvi1();
    void canvi2();
    void canvi3();

  signals:
    void camOrto();
    void camPers();
    void but1();
    void but2();
    void but3();

};
