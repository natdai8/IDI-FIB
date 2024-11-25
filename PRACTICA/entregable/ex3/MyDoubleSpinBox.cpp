#include "MyDoubleSpinBox.h"

MyDoubleSpinBox::MyDoubleSpinBox(QWidget* parent): QDoubleSpinBox(parent)
{

}

void MyDoubleSpinBox::reset()
{
    QString a = QString::number(0, 'f', 2);
    double num = a.split(" ")[0].toInt();
    setValue(num);
}
