/********************************************************************************
** Form generated from reading UI file 'cframe.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CFRAME_H
#define UI_CFRAME_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_cframe
{
public:
    QWidget *centralwidget;
    QStackedWidget *stackedWidget;
    QWidget *page_2;
    QRadioButton *radioButton;
    QLabel *label_2;
    QWidget *page;
    QLabel *label;
    QPushButton *btnsalir;
    QPushButton *pushButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *cframe)
    {
        if (cframe->objectName().isEmpty())
            cframe->setObjectName("cframe");
        cframe->resize(1543, 858);
        centralwidget = new QWidget(cframe);
        centralwidget->setObjectName("centralwidget");
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setGeometry(QRect(0, 0, 1541, 811));
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        radioButton = new QRadioButton(page_2);
        radioButton->setObjectName("radioButton");
        radioButton->setGeometry(QRect(740, 420, 112, 26));
        label_2 = new QLabel(page_2);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(620, 240, 281, 71));
        label_2->setPixmap(QPixmap(QString::fromUtf8(":/Imagenes/Canvas-Logo-transparent-Large.png")));
        label_2->setScaledContents(true);
        label_2->setWordWrap(false);
        stackedWidget->addWidget(page_2);
        page = new QWidget();
        page->setObjectName("page");
        label = new QLabel(page);
        label->setObjectName("label");
        label->setGeometry(QRect(0, 0, 81, 761));
        label->setPixmap(QPixmap(QString::fromUtf8(":/Imagenes/Barra canvas.PNG")));
        label->setScaledContents(true);
        btnsalir = new QPushButton(page);
        btnsalir->setObjectName("btnsalir");
        btnsalir->setEnabled(true);
        btnsalir->setGeometry(QRect(0, 730, 81, 31));
        btnsalir->setContextMenuPolicy(Qt::ContextMenuPolicy::PreventContextMenu);
        btnsalir->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        pushButton = new QPushButton(page);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(1450, 180, 83, 29));
        stackedWidget->addWidget(page);
        cframe->setCentralWidget(centralwidget);
        menubar = new QMenuBar(cframe);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1543, 25));
        cframe->setMenuBar(menubar);
        statusbar = new QStatusBar(cframe);
        statusbar->setObjectName("statusbar");
        cframe->setStatusBar(statusbar);

        retranslateUi(cframe);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(cframe);
    } // setupUi

    void retranslateUi(QMainWindow *cframe)
    {
        cframe->setWindowTitle(QCoreApplication::translate("cframe", "cframe", nullptr));
        radioButton->setText(QCoreApplication::translate("cframe", "RadioButton", nullptr));
        label_2->setText(QString());
        label->setText(QString());
        btnsalir->setText(QString());
        pushButton->setText(QCoreApplication::translate("cframe", "PushButton", nullptr));
    } // retranslateUi

};

namespace Ui {
    class cframe: public Ui_cframe {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CFRAME_H
