#include "MyLabel.h"

MyLabel::MyLabel(QWidget* parent): QLabel(parent)
{
    // altres
}

void MyLabel::truncarLabel(int n) 
{
	QString q = textOriginal;
	q.truncate(n);
	setText(q); 	//funcio en designer
}

void MyLabel::actualizar(QString txt) 
{
	textOriginal = txt;
}
