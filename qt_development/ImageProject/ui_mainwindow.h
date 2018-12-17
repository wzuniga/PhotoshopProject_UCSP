/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
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
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1156, 646);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(110, 230, 300, 300));
        readBMP = new QPushButton(centralWidget);
        readBMP->setObjectName(QStringLiteral("readBMP"));
        readBMP->setGeometry(QRect(110, 60, 114, 32));
        readBMP->setAutoDefault(true);
        readBMP->setFlat(false);
        convolution = new QPushButton(centralWidget);
        convolution->setObjectName(QStringLiteral("convolution"));
        convolution->setGeometry(QRect(270, 60, 131, 32));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(110, 20, 59, 16));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(270, 20, 59, 16));
        filterSize = new QLineEdit(centralWidget);
        filterSize->setObjectName(QStringLiteral("filterSize"));
        filterSize->setGeometry(QRect(280, 90, 113, 21));
        filterSize->setMaxLength(2);
        imgConvo = new QLabel(centralWidget);
        imgConvo->setObjectName(QStringLiteral("imgConvo"));
        imgConvo->setGeometry(QRect(600, 230, 300, 300));
        polinomial = new QPushButton(centralWidget);
        polinomial->setObjectName(QStringLiteral("polinomial"));
        polinomial->setGeometry(QRect(430, 60, 161, 32));
        spinBox_1 = new QSpinBox(centralWidget);
        spinBox_1->setObjectName(QStringLiteral("spinBox_1"));
        spinBox_1->setGeometry(QRect(440, 90, 42, 22));
        spinBox_2 = new QSpinBox(centralWidget);
        spinBox_2->setObjectName(QStringLiteral("spinBox_2"));
        spinBox_2->setGeometry(QRect(490, 90, 42, 22));
        spinBox_2->setMinimum(1);
        spinBox_3 = new QSpinBox(centralWidget);
        spinBox_3->setObjectName(QStringLiteral("spinBox_3"));
        spinBox_3->setGeometry(QRect(540, 90, 42, 22));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(110, 200, 121, 16));
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(600, 200, 91, 16));
        outputAlg = new QLabel(centralWidget);
        outputAlg->setObjectName(QStringLiteral("outputAlg"));
        outputAlg->setGeometry(QRect(710, 200, 221, 16));
        dft = new QPushButton(centralWidget);
        dft->setObjectName(QStringLiteral("dft"));
        dft->setGeometry(QRect(630, 60, 114, 32));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1156, 22));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        readBMP->setDefault(false);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Image Project", Q_NULLPTR));
        label->setText(QString());
        readBMP->setText(QApplication::translate("MainWindow", "Read BMP", Q_NULLPTR));
        convolution->setText(QApplication::translate("MainWindow", "Convolution", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "Tema 1", Q_NULLPTR));
        label_3->setText(QApplication::translate("MainWindow", "Tema 2", Q_NULLPTR));
        filterSize->setText(QApplication::translate("MainWindow", "3", Q_NULLPTR));
        filterSize->setPlaceholderText(QApplication::translate("MainWindow", "Number Matrix", Q_NULLPTR));
        imgConvo->setText(QString());
        polinomial->setText(QApplication::translate("MainWindow", "Polinomial", Q_NULLPTR));
        label_4->setText(QApplication::translate("MainWindow", "Input Image", Q_NULLPTR));
        label_5->setText(QApplication::translate("MainWindow", "Output Image", Q_NULLPTR));
        outputAlg->setText(QString());
        dft->setText(QApplication::translate("MainWindow", "DFT", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
