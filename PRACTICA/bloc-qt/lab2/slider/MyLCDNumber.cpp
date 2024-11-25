#include "MyLCDNumber.h"

MyLCDNumber::MyLCDNumber(QWidget* parent): QLCDNumber(parent)
{
    // altres
}

void MyLCDNumber::canviColor(int n)
{
    if (n == 0) setStyleSheet("color: green");     // verd
    else if (n % 2 == 0) setStyleSheet("color: blue");        // blau
    else setStyleSheet("color: red");          // vermell

    display(n);
}

void MyLCDNumber::setNull()
{
    setStyleSheet("color: green");
    display(0);
}
