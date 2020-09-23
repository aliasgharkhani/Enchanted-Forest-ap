#include "help.h"
#include "ui_help.h"
#include <QtMultimedia/QSoundEffect>
#include <QObject>



Help::Help(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Help)
{
    ui->setupUi(this);
    //ui->scrollArea->setWidget(ui->label_2);

    ui->scrollArea->setWidget(ui->label);
}

Help::~Help()
{
    delete ui;
}

void Help::on_pushButton_clicked()
{

    this->close();
}


