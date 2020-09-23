#include "rolldialog.h"
#include "ui_rolldialog.h"

RollDialog::RollDialog(QWidget *parent, int* first_roll, int* second_roll) :
    QDialog(parent),
    ui(new Ui::RollDialog)
{
    ui->setupUi(this);
    this->first_roll = first_roll;
    this->second_roll = second_roll;
    ui->Roll_1->setValue(*first_roll);
    ui->Roll_2->setValue(*second_roll);
}

RollDialog::~RollDialog()
{
    delete ui;
}

void RollDialog::on_Button_clicked()
{
    int n = this->ui->Roll_1->value();
    int m = this->ui->Roll_2->value();
//    if( !(n == 1 || n == 2 || n == 3 || n == 4 || n == 5 || n == 6) || !(m == 1 || m == 2 || m == 3 || m == 4 || m == 5 || m == 6)){
//        QString exception;
//        exception = "تاس(ها) درست وارد نشده‌اند!";
//        throw exception;
//    }
    *this->first_roll = ui->Roll_1->value();
    *this->second_roll = ui->Roll_2->value();
    this->close();
}
