/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QLabel *label;
    QPushButton *readBMP;
    QPushButton *convolution;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *filterSize;
    QLabel *imgConvo;
    QPushButton *polinomial;
    QSpinBox *spinBox_1;
    QSpinBox *spinBox_2;
    QSpinBox *spinBox_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *outputAlg;
    QPushButton *dft;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1156, 646);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(110, 230, 300, 300));
        readBMP = new QPushButton(centralWidget);
        readBMP->setObjectName(QString::fromUtf8("readBMP"));
        readBMP->setGeometry(QRect(110, 60, 114, 32));
        readBMP->setAutoDefault(true);
        readBMP->setFlat(false);
        convolution = new QPushButton(centralWidget);
        convolution->setObjectName(QString::fromUtf8("convolution"));
        convolution->setGeometry(QRect(270, 60, 131, 32));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(110, 20, 59, 16));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(270, 20, 59, 16));
        filterSize = new QLineEdit(centralWidget);
        filterSize->setObjectName(QString::fromUtf8("filterSize"));
        filterSize->setGeometry(QRect(280, 90, 113, 21));
        filterSize->setMaxLength(2);
        imgConvo = new QLabel(centralWidget);
        imgConvo->setObjectName(QString::fromUtf8("imgConvo"));
        imgConvo->setGeometry(QRect(600, 230, 300, 300));
        polinomial = new QPushButton(centralWidget);
        polinomial->setObjectName(QString::fromUtf8("polinomial"));
        polinomial->setGeometry(QRect(430, 60, 161, 32));
        spinBox_1 = new QSpinBox(centralWidget);
        spinBox_1->setObjectName(QString::fromUtf8("spinBox_1"));
        spinBox_1->setGeometry(QRect(440, 90, 42, 22));
        spinBox_2 = new QSpinBox(centralWidget);
        spinBox_2->setObjectName(QString::fromUtf8("spinBox_2"));
        spinBox_2->setGeometry(QRect(490, 90, 42, 22));
        spinBox_2->setMinimum(1);
        spinBox_3 = new QSpinBox(centralWidget);
        spinBox_3->setObjectName(QString::fromUtf8("spinBox_3"));
        spinBox_3->setGeometry(QRect(540, 90, 42, 22));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(110, 200, 121, 16));
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(600, 200, 91, 16));
        outputAlg = new QLabel(centralWidget);
        outputAlg->setObjectName(QString::fromUtf8("outputAlg"));
        outputAlg->setGeometry(QRect(710, 200, 221, 16));
        dft = new QPushButton(centralWidget);
        dft->setObjectName(QString::fromUtf8("dft"));
        dft->setGeometry(QRect(630, 60, 114, 32));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1156, 22));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        readBMP->setDefault(false);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Image Project", nullptr));
        label->setText(QString());
        readBMP->setText(QApplication::translate("MainWindow", "Read BMP", nullptr));
        convolution->setText(QApplication::translate("MainWindow", "Convolution", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "Tema 1", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "Tema 2", nullptr));
        filterSize->setText(QApplication::translate("MainWindow", "3", nullptr));
        filterSize->setPlaceholderText(QApplication::translate("MainWindow", "Number Matrix", nullptr));
        imgConvo->setText(QString());
        polinomial->setText(QApplication::translate("MainWindow", "Polinomial", nullptr));
        label_4->setText(QApplication::translate("MainWindow", "Input Image", nullptr));
        label_5->setText(QApplication::translate("MainWindow", "Output Image", nullptr));
        outputAlg->setText(QString());
        dft->setText(QApplication::translate("MainWindow", "DFT", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
