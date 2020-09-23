#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "dragwidget.h"
#include <QMainWindow>
#include <fstream>
#include <QEventLoop>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0, QEventLoop* editor_wait = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_12_clicked();

private:
    std::string address = "";
    QEventLoop* wait;
    int green_cell_number = 0;
    std::fstream positions;
    std::fstream neighbourfile;
    int neighbours[2];
    int orange_counter = 0;
    DragWidget mydragwidget;
    bool firstnode = true;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
