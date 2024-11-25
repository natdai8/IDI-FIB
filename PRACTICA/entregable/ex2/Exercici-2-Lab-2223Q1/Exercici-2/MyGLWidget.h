#include "LL2GLWidget.h"

#include "model.h"

class MyGLWidget : public LL2GLWidget {
  Q_OBJECT

  public:
    MyGLWidget(QWidget *parent=0) : LL2GLWidget(parent) {}
    ~MyGLWidget();

  private:

    int printOglError(const char file[], int line, const char func[]);

    int grauY = 0, grauYP = 0, grauM = 0, grauEM = 0, grauJ = 0;
    float ra = 1.0f;
    float d = 0, alfa_inicial = 0;
    int portal = 1, pov = 0;
    bool evilmorty = false;

    GLuint mortyLoc = 1;
    glm::vec3 posMortyVermell = glm::vec3(0,0,0);


  protected:

    virtual void RickTransform();
    virtual void MortyTransform ();
    virtual void MortyVermellTransform ();
    virtual void PortalTransform();
    virtual void viewTransform();
    virtual void projectTransform();
    virtual void iniCamera();
    virtual void carregaShaders();
    virtual void funcionPortal(glm::vec3 posMorty);
    virtual void mouseMoveEvent(QMouseEvent *e);
    virtual void keyPressEvent(QKeyEvent* event);
    virtual void paintGL();
    virtual bool MortyPortalTest(float angleRick, glm::vec3 posMorty);
};
