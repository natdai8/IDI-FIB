#include "MyLabel.h"

MyLabel::MyLabel(QWidget* parent): QLabel(parent)
{

}

void MyLabel::actPeatge()
{
	obert = !obert;
	if (obert) setStyleSheet("background-color: green");
	else setStyleSheet("background-color: red");
}

void MyLabel::rcotxe()
{
	if (si) {
		recaudat++;
		setNum(recaudat);
	}
}

void MyLabel::rcamio()
{
	if (si) {
		recaudat += 4;
		setNum(recaudat);
	}
}

void MyLabel::rmoto()
{
	if (si) {
		recaudat++;
		setNum(recaudat);
	}
}

void MyLabel::comprovar(bool a)
{
    si = a;
}

