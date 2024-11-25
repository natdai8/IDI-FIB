// MyGLWidget.h
#include "LL4GLWidget.h"

class MyGLWidget : public LL4GLWidget {

  Q_OBJECT

  public:

    MyGLWidget(QWidget *parent=0) : LL4GLWidget(parent) {}
    ~MyGLWidget();

  protected:

    virtual void mouseMoveEvent(QMouseEvent *e);
    virtual void keyPressEvent(QKeyEvent* event);
    virtual void initializeGL();
    virtual void paintGL();
    virtual void iniEscena();
    virtual void projectTransform ();
    virtual void viewTransform ();
    virtual void modelTransformMorty();
    virtual void modelTransformFantasma();
    virtual void carregaShaders();

    GLuint colorFocusLoc, posFocusLoc1, posFocusLoc2, posFocusLoc3, posFocusLoc4;
    GLuint colorFocusLocM, posFocusLocM, transLocM;

    glm::vec3 posFocus1, posFocus2, posFocus3, posFocus4, colorFocus;
    glm::vec3 posFocusM, colorFocusM;

    glm::mat4 TGM;

    int grauM = 90;

    int llumM = 1, llumE = 1, apareix = 1;

    double boox = 0.0;

  private:

    int printOglError(const char file[], int line, const char func[]);
};
