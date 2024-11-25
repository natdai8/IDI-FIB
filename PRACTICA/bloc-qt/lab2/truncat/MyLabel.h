#include <QLabel>

class MyLabel : public QLabel
{
    Q_OBJECT

    public:
    
        MyLabel(QWidget *parent);
        QString textOriginal;

    public slots:
    
        void truncarLabel(int);
        void actualizar(QString);
        
};
