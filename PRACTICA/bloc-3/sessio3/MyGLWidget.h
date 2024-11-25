// MyGLWidget.h
#include "BL3GLWidget.h"

class MyGLWidget : public BL3GLWidget {
  Q_OBJECT

  public:
    MyGLWidget(QWidget *parent=0) : BL3GLWidget(parent) {}
    ~MyGLWidget();

  protected:
    virtual void mouseMoveEvent(QMouseEvent *e);
    virtual void keyPressEvent(QKeyEvent* event);
    virtual void initializeGL();
    virtual void paintGL();
    virtual void creaBuffersPatricio();
    virtual void carregaShaders();
    virtual void iniMaterialTerra ();
    virtual void calculaCapsaModel();
    virtual void modelTransformPatricio();

    GLuint colorFocusLoc, posFocusLoc, colorFocusLocEsc, posFocusLocEsc, escenaLoc;

    glm::vec3 posFocus, colorFocus, posFocusEsc, colorFocusEsc;

    int escena, llum = 1, llum2 = 1, bc = 0;

    glm::vec3 suelo;


  private:
    int printOglError(const char file[], int line, const char func[]);
};
