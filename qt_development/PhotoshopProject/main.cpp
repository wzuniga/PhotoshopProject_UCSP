#include <QApplication>
#include <QMainWindow>
#include "mainwindow.h"
#include "ui_mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QWidget *widget = new QWidget;
    Ui::MainWindow ui;
    ui.setupUi(*widget);

    widget->show();
    return app.exec();
}
