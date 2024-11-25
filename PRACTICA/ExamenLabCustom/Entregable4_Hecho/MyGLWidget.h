// MyGLWidget.h
#include "LL4GLWidget.h"

class MyGLWidget : public LL4GLWidget {
  Q_OBJECT
  public:
    MyGLWidget(QWidget *parent=0) : LL4GLWidget(parent) {}
    ~MyGLWidget();
    virtual void initializeGL();
    void carregaShaders_nuevos();
    virtual void modelTransformMorty();
    virtual void modelTransformFantasma();
    virtual void paintGL();
    virtual void viewTransform();
    virtual void projectTransform();
    void reset();
    
  protected:
    virtual void mouseMoveEvent(QMouseEvent *e);
    virtual void keyPressEvent(QKeyEvent* event);
  
  private:
    int printOglError(const char file[], int line, const char func[]);
    
    //Posició i color dels focus (Vectors i Uniforms pel vertex shader)
    glm::vec3 posFocus1, posFocus2, posFocus3, posFocus4, posFocusLinterna, posFocusAzul, posFocusBlanco;
    glm::vec3 colFocus1, colFocus2, colFocus3, colFocus4, colFocusLinterna, colFocusAzul, colFocusBlanco;
    GLuint posFocus1Loc, colFocus1Loc, posFocus2Loc, colFocus2Loc, posFocus3Loc, colFocus3Loc, posFocus4Loc, colFocus4Loc, posFocusLinternaLoc, colFocusLinternaLoc, colFocusAzulLoc, posFocusAzulLoc, colFocusBlancoLoc, posFocusBlancoLoc;
    
    glm::mat4 TGLinterna;
    GLuint TGLinternaLoc;
    
    int rotMorty = 0;
    glm::vec3 posFantasma = glm::vec3(0.0,0.0,0.0);

    //-------------------------------
    int g = 1, f = 1, n = 1, pers = 1;
    float grauF = 0, altura = 0, alturaM = 2, zn = radiEsc, zf = radiEsc*3.0f, cam = 4;
   // glm::vec3 vrpMorty(6, 2, 5);

  public slots:

    void rotarMorty(int);
    void canviO();
    void canviP();

  signals:

    void actualizar(int);
    void actCamaraO();
    void actCamaraP();
};
