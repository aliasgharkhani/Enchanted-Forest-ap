#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtWidgets>
#include <QObject>
#include "dragwidget.h"
#include <fstream>
#include <QPushButton>
#include <QDialog>
#include "help.h"
#include "wellcome.h"
MainWindow::MainWindow(QWidget *parent, QEventLoop* editor_wait) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->wait = editor_wait;
    Wellcome *wellcome_page = new Wellcome(this);
    wellcome_page->show();
    ui->horizontalLayout->addWidget(&this->mydragwidget);
    std::fstream neighbourfile1;
    neighbourfile1.open(this->address + "neighbours.txt", std::ios::out);
    neighbourfile1 << "";
    neighbourfile1.close();
}

MainWindow::~MainWindow()
{


    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    int number1, x, y, aux = 0;
    std::string color;
    std::fstream myfile;
    myfile.open(this->address + "positions.txt");

    if(this->green_cell_number != 0){
        aux = this->green_cell_number;
    }

    while (myfile >> number1) {
        myfile >> x >> y >> color;
        mydragwidget.greencells[aux + number1 - 1] = new QLabel(&mydragwidget);
        mydragwidget.greencells[aux + number1 - 1]->move(x, y);
        if(color == "orange"){
            mydragwidget.greencells[aux + number1 - 1]->setPixmap(QPixmap(":/resources/PNG/Orange.png"));
            mydragwidget.greencells[aux + number1 - 1]->setObjectName("orange");
        }
        if(color == "violet"){
            mydragwidget.greencells[aux + number1 - 1]->setPixmap(QPixmap(":/resources/PNG/Violet.png"));
            mydragwidget.greencells[aux + number1 - 1]->setObjectName("violet");
        }
        if(color == "green"){
            mydragwidget.greencells[aux + number1 - 1]->setPixmap(QPixmap(":/resources/PNG/Green.png"));
            mydragwidget.greencells[aux + number1 - 1]->setObjectName("green");
        }
        if(color == "red"){
            mydragwidget.greencells[aux + number1 - 1]->setPixmap(QPixmap(":/resources/PNG/Red.png"));
            mydragwidget.greencells[aux + number1 - 1]->setObjectName("red");
        }
        mydragwidget.greencells[aux + number1 - 1]->setAccessibleName(QString::number(aux + number1));

        mydragwidget.greencells[aux + number1 - 1]->show();
    }
    this->green_cell_number = aux + number1;
    myfile.close();
//    QLabel *bluecell1 = new QLabel(&mydragwidget);
//    bluecell1->move(50, 320);
//    bluecell1->setPixmap(QPixmap("/home/ali/project/RazeJangal/PNG/Blue.png"));
//    bluecell1->show();
//    QLabel *bluecell2 = new QLabel(&mydragwidget);
//    bluecell2->move(10, 360);
//    bluecell2->setPixmap(QPixmap("/home/ali/project/RazeJangal/PNG/Blue.png"));
//    bluecell2->show();
//    QLabel *bluecell3 = new QLabel(&mydragwidget);
//    bluecell3->move(10, 410);
//    bluecell3->setPixmap(QPixmap("/home/ali/project/RazeJangal/PNG/Blue.png"));
//    bluecell3->show();
//    QLabel *bluecell4 = new QLabel(&mydragwidget);
//    bluecell4->move(40, 450);
//    bluecell4->setPixmap(QPixmap("/home/ali/project/RazeJangal/PNG/Blue.png"));
//    bluecell4->show();


}

void MainWindow::on_pushButton_2_clicked()
{
    this->neighbourfile.open(this->address + "neighbours.txt", std::ios::out);
    this->neighbourfile << "";
    this->firstnode = true;
    this->neighbourfile.close();
}

void MainWindow::on_pushButton_3_clicked()
{
    mydragwidget.greencells[mydragwidget.current_cell_number - 1]->setPixmap(QPixmap(":/resources/PNG/Red.png"));
    mydragwidget.greencells[mydragwidget.current_cell_number - 1]->setObjectName("red");
    ui->pushButton_3->setVisible(false);

}

void MainWindow::on_pushButton_4_clicked()
{
    mydragwidget.greencells[mydragwidget.current_cell_number - 1]->setPixmap(QPixmap(":/resources/PNG/Orange.png"));
    mydragwidget.greencells[mydragwidget.current_cell_number - 1]->setObjectName("orange");
    this->orange_counter ++;
    if(this->orange_counter == 13)
        ui->pushButton_4->setVisible(false);
}

void MainWindow::on_pushButton_5_clicked()
{
    mydragwidget.greencells[mydragwidget.current_cell_number - 1]->setPixmap(QPixmap(":/resources/PNG/Violet.png"));
    mydragwidget.greencells[mydragwidget.current_cell_number - 1]->setObjectName("violet");
    ui->pushButton_5->setVisible(false);
}



void MainWindow::on_pushButton_7_clicked()
{
    if(!(this->firstnode)){
        this->neighbourfile << this->mydragwidget.current_cell_number << "\n";
        this->firstnode = true;
        this->neighbourfile.close();
        return;
    }
    if(this->firstnode){
        this->firstnode = false;
        this->neighbourfile.open(this->address + "neighbours.txt", std::ios::app);
        this->neighbourfile << this->mydragwidget.current_cell_number << " ";
        return;
    }

}

//void MainWindow::on_pushButton_8_clicked()
//{
//    mydragwidget.greencells[mydragwidget.current_cell_number - 1]->move(7, 7);
//}

void MainWindow::on_pushButton_9_clicked()
{
    mydragwidget.greencells[this->green_cell_number] = new QLabel(&mydragwidget);
    mydragwidget.greencells[this->green_cell_number]->move(7, 7);
    mydragwidget.greencells[this->green_cell_number]->setPixmap(QPixmap(":/resources/PNG/Green.png"));
    mydragwidget.greencells[this->green_cell_number]->setAccessibleName(QString::number(this->green_cell_number + 1));
    mydragwidget.greencells[this->green_cell_number]->setObjectName("green");
    mydragwidget.greencells[this->green_cell_number]->show();
    this->green_cell_number ++;
    this->neighbourfile.open(this->address + "neighbours.txt", std::ios::out);
    this->neighbourfile << "";
    this->neighbourfile.close();
}

void MainWindow::on_pushButton_8_clicked()
{
    this->positions.open(this->address + "newpositions.txt", std::ios::out);
    for(int u=0;u < this->green_cell_number;u++){
        if(mydragwidget.greencells[u]->pos().x() == -40)
            continue;
        this->positions << (u + 1) << "  ";
        this->positions << mydragwidget.greencells[u]->pos().x() << " ";
        this->positions << mydragwidget.greencells[u]->pos().y() << " ";
        this->positions << mydragwidget.greencells[u]->objectName().toStdString() << "\n";
    }
    this->positions.close();
    //this->wait->exit();
    this->close();
    this->wait->exit();
}

void MainWindow::on_pushButton_10_clicked()
{
    Help *mydialog = new Help(this);
    mydialog->show();
}

void MainWindow::on_pushButton_11_clicked()
{
    ui->pushButton_3->setVisible(true);
    ui->pushButton_4->setVisible(true);
    ui->pushButton_5->setVisible(true);
    this->orange_counter = 0;

    for(int e=0; e < this->green_cell_number;e++){
        mydragwidget.greencells[e]->setVisible(false);
    }
    this->green_cell_number = 0;
    this->firstnode = true;
    this->neighbourfile.open(this->address + "neighbours.txt", std::ios::out);
    this->neighbourfile << "";
    this->neighbourfile.close();
    this->positions.open(this->address + "newpositions.txt", std::ios::out);
    this->positions << "";
    this->positions.close();
}

void MainWindow::on_pushButton_12_clicked()
{
    this->neighbourfile.open(this->address + "neighbours.txt", std::ios::app);
    this->neighbourfile << 0 << " " <<this->mydragwidget.current_cell_number << "\n";
    this->neighbourfile.close();
    ui->pushButton_12->setVisible(false);
}
