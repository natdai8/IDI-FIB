#include <QLCDNumber>

class MyLCDNumber: public QLCDNumber
{
    Q_OBJECT

    public:
        MyLCDNumber (QWidget *parent);
        int countCotxe = 0;
        int countCamio = 0;
        int countMoto = 0;
        bool obert = false;

    public slots:
        void comprovar(bool);
        void cotxe();
        void camio();
        void moto();
};
