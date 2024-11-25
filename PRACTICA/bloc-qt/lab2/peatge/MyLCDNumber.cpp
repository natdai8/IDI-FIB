#include "MyLCDNumber.h"

MyLCDNumber::MyLCDNumber(QWidget* parent): QLCDNumber(parent)
{

}

void MyLCDNumber::comprovar(bool a)
{
    obert = a;
}

void MyLCDNumber::cotxe()
{
	if (obert) {
		countCotxe++;
		display(countCotxe);
	}
}

void MyLCDNumber::camio()
{
	if (obert) {
		countCamio++;
		display(countCamio);
	}
}

void MyLCDNumber::moto()
{
	if (obert) {
		countMoto++;
		display(countMoto);
	}
}
