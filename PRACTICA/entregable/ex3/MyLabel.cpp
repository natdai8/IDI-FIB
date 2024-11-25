#include "MyLabel.h"
#include <cmath>

MyLabel::MyLabel(QWidget* parent): QLabel(parent)
{

}

void MyLabel::calcNotaFinal()
{
    if (notaLab >= 4.5) {
        nL = (notaLab + pow((countTotal / 4.0), 2.2)) * 0.25;
        notaFinal = nL + nP + nF;
    }
    else {
        nL = notaLab * 0.25;
        notaFinal = nL + nP + nF;
    }
    notaFinal = qMin(10.0, round(notaFinal * 100) / 100);
    QString a = QString::number(notaFinal, 'f', 2);
    setText(a);
    actNota();
}

void MyLabel::calcNotaExParcial (double notaP)
{
    nP = notaP * 0.25;
    calcNotaFinal();
}

void MyLabel::calcNotaExLab (double notaL)
{
    notaLab = notaL;
    calcNotaFinal();
}

void MyLabel::calcNotaExFinal (double notaF)
{
    nF = notaF * 0.50;
    calcNotaFinal();
}

void MyLabel::calcEntregable (bool pres)
{
    if (pres) countTotal++;
    else countTotal--;
    calcNotaFinal();
}

void MyLabel::actNota()
{
    if (notaFinal < 5.00) setStyleSheet("color: red");
    else setStyleSheet("color: green");
}

void MyLabel::reset()
{
    setStyleSheet("color:red");
    QString a = QString::number(0, 'f', 2);
    setText(a);
}

void MyLabel::reset2()
{
    QString a = QString::number(10, 'f', 2);
    setText(a);
}

void MyLabel::notaPerTreureP (double notaP)
{
    nP = notaP * 0.25;
    double treure = (5.0-(nP+nL))/0.5;
    QString a = QString::number(treure, 'f', 2);
    if (nF == 0.0) setText(a);
}

void MyLabel::notaPerTreureL (double notaL)
{
    nL = notaL * 0.25;
    double treure = (5.0-(nP+nL))/0.5;
    QString a = QString::number(treure, 'f', 2);
    if (nF == 0.0) setText(a);
}



