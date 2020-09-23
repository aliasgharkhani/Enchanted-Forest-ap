#include "wellcome.h"
#include "ui_wellcome.h"
#include <QtMultimedia/QSoundEffect>

Wellcome::Wellcome(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Wellcome)
{
    ui->setupUi(this);
}

Wellcome::~Wellcome()
{
    delete ui;
}

void Wellcome::on_pushButton_clicked()
{
    this->close();
}
