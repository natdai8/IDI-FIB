/********************************************************************************
** Form generated from reading UI file 'MyForm.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYFORM_H
#define UI_MYFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "MyLCDNumber.h"
#include "MyLabel.h"

QT_BEGIN_NAMESPACE

class Ui_MyForm
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_6;
    QVBoxLayout *verticalLayout_3;
    MyLabel *label;
    QRadioButton *radioButton;
    QSpacerItem *horizontalSpacer_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    MyLCDNumber *lcdNumber;
    QPushButton *pushButton;
    QHBoxLayout *horizontalLayout_7;
    MyLCDNumber *lcdNumber_2;
    QPushButton *pushButton_2;
    QHBoxLayout *horizontalLayout_3;
    MyLCDNumber *lcdNumber_3;
    QPushButton *pushButton_3;
    QVBoxLayout *verticalLayout_4;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_5;
    MyLabel *label_2;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_4;

    void setupUi(QWidget *MyForm)
    {
        if (MyForm->objectName().isEmpty())
            MyForm->setObjectName(QString::fromUtf8("MyForm"));
        MyForm->resize(476, 273);
        gridLayout = new QGridLayout(MyForm);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        label = new MyLabel(MyForm);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        QFont font;
        font.setKerning(true);
        label->setFont(font);

        verticalLayout_3->addWidget(label);

        radioButton = new QRadioButton(MyForm);
        radioButton->setObjectName(QString::fromUtf8("radioButton"));

        verticalLayout_3->addWidget(radioButton);


        horizontalLayout_6->addLayout(verticalLayout_3);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_2);


        gridLayout->addLayout(horizontalLayout_6, 0, 0, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        lcdNumber = new MyLCDNumber(MyForm);
        lcdNumber->setObjectName(QString::fromUtf8("lcdNumber"));

        horizontalLayout->addWidget(lcdNumber);

        pushButton = new QPushButton(MyForm);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        horizontalLayout->addWidget(pushButton);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        lcdNumber_2 = new MyLCDNumber(MyForm);
        lcdNumber_2->setObjectName(QString::fromUtf8("lcdNumber_2"));

        horizontalLayout_7->addWidget(lcdNumber_2);

        pushButton_2 = new QPushButton(MyForm);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        horizontalLayout_7->addWidget(pushButton_2);


        verticalLayout->addLayout(horizontalLayout_7);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        lcdNumber_3 = new MyLCDNumber(MyForm);
        lcdNumber_3->setObjectName(QString::fromUtf8("lcdNumber_3"));

        horizontalLayout_3->addWidget(lcdNumber_3);

        pushButton_3 = new QPushButton(MyForm);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));

        horizontalLayout_3->addWidget(pushButton_3);


        verticalLayout->addLayout(horizontalLayout_3);


        gridLayout->addLayout(verticalLayout, 0, 1, 1, 1);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_2 = new MyLabel(MyForm);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_5->addWidget(label_2);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);

        pushButton_4 = new QPushButton(MyForm);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));

        horizontalLayout_4->addWidget(pushButton_4);


        horizontalLayout_5->addLayout(horizontalLayout_4);


        verticalLayout_4->addLayout(horizontalLayout_5);


        gridLayout->addLayout(verticalLayout_4, 1, 0, 1, 2);


        retranslateUi(MyForm);
        QObject::connect(pushButton_4, SIGNAL(clicked()), MyForm, SLOT(close()));
        QObject::connect(radioButton, SIGNAL(clicked()), label, SLOT(actPeatge()));
        QObject::connect(pushButton, SIGNAL(clicked()), lcdNumber, SLOT(cotxe()));
        QObject::connect(radioButton, SIGNAL(clicked(bool)), lcdNumber, SLOT(comprovar(bool)));
        QObject::connect(radioButton, SIGNAL(clicked(bool)), lcdNumber_3, SLOT(comprovar(bool)));
        QObject::connect(pushButton_3, SIGNAL(clicked()), lcdNumber_3, SLOT(camio()));
        QObject::connect(pushButton_2, SIGNAL(clicked()), lcdNumber_2, SLOT(moto()));
        QObject::connect(radioButton, SIGNAL(clicked(bool)), lcdNumber_2, SLOT(comprovar(bool)));
        QObject::connect(pushButton_3, SIGNAL(clicked()), label_2, SLOT(rcamio()));
        QObject::connect(pushButton_2, SIGNAL(clicked()), label_2, SLOT(rmoto()));
        QObject::connect(pushButton, SIGNAL(clicked()), label_2, SLOT(rcotxe()));
        QObject::connect(radioButton, SIGNAL(clicked(bool)), label_2, SLOT(comprovar(bool)));

        QMetaObject::connectSlotsByName(MyForm);
    } // setupUi

    void retranslateUi(QWidget *MyForm)
    {
        MyForm->setWindowTitle(QCoreApplication::translate("MyForm", "Form", nullptr));
#if QT_CONFIG(tooltip)
        label->setToolTip(QCoreApplication::translate("MyForm", "<html><head/><body><p align=\"center\"><br/>Tancat/Obert</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label->setText(QCoreApplication::translate("MyForm", "Tancat/Obert", nullptr));
        radioButton->setText(QCoreApplication::translate("MyForm", "Obrir el pas", nullptr));
        pushButton->setText(QCoreApplication::translate("MyForm", "Cotxe", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MyForm", "Moto", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MyForm", "Cami\303\263", nullptr));
        label_2->setText(QCoreApplication::translate("MyForm", "Recaptaci\303\263 Total", nullptr));
        pushButton_4->setText(QCoreApplication::translate("MyForm", "Exit", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MyForm: public Ui_MyForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYFORM_H
