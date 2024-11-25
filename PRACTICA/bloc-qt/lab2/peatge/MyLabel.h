#include <QLabel>

class MyLabel: public QLabel
{
    Q_OBJECT

    public:
        MyLabel (QWidget *parent);
        bool obert = false;
        bool si = false;
        int recaudat = 0;

    public slots:
        void actPeatge();
        void rcotxe();
        void rcamio();
        void rmoto();
        void comprovar(bool);
};
