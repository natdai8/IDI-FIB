#include "MyCheckBox.h"
#include <cmath>

MyCheckBox::MyCheckBox(QWidget* parent): QCheckBox(parent)
{

}

void MyCheckBox::reset()
{
    setChecked(false);
}
