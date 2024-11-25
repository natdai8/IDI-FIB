#include <QLabel>

class MyLabel: public QLabel
{
    Q_OBJECT

    public:

        MyLabel (QWidget *parent);
        double notaFinal = 0.00, nL = 0.00, nP = 0.00, nF = 0.00;
        double notaLab = 0.0;
        int countTotal = 0;

    public slots:

        void calcNotaFinal();
        void calcNotaExParcial(double);
        void calcNotaExLab(double);
        void calcNotaExFinal(double);
        void calcEntregable(bool);

        void actNota();

        void reset();
        void reset2();

        void notaPerTreureL(double);
        void notaPerTreureP(double);

};
