TEMPLATE    = app
QT         += opengl 

INCLUDEPATH +=  /usr/include/glm
INCLUDEPATH +=	/home/natalia/Escritorio/idi/Model

FORMS += MyForm.ui

HEADERS += MyForm.h BL2GLWidget.h MyGLWidget.h

SOURCES += main.cpp MyForm.cpp \
        BL2GLWidget.cpp MyGLWidget.cpp
SOURCES +=     /home/natalia/Escritorio/idi/Model/model.cpp
