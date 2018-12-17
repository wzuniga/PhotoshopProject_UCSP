#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QPixmap pixelMap;
    int height_map;
    int widgt_map;
    unsigned char* charMap;

private slots:
    void on_read_pressed();
    void on_convolution_pressed();
};

#endif // MAINWINDOW_H
