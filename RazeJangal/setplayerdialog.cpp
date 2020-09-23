#include "setplayerdialog.h"
#include "ui_setplayerdialog.h"

SetPlayerDialog::SetPlayerDialog(QWidget *parent, int* number_of_players, std::vector<QString>* names) :
    QDialog(parent),
    ui(new Ui::SetPlayerDialog)
{
    ui->setupUi(this);
    this->closed_by_button = false;
    this->names = names;
    this->number_of_players = number_of_players;
    ui->Player_name_3->setEnabled(false);
    ui->Player_name_4->setEnabled(false);
    ui->message_5->setEnabled(false);
    ui->message_6->setEnabled(false);
}

SetPlayerDialog::~SetPlayerDialog()
{
    if(!closed_by_button){
        QString exception;
        exception = "برنامه بسته شد!";
        throw exception;
    }

    delete ui;
}

void SetPlayerDialog::on_Button_clicked()
{
    int n = ui->number_of_players->value();
    if(!(n == 2 || n == 3 || n == 4)){
        QString exception;
        exception = "تعداد بازیکنان وارد نشده است!";
        throw exception;
    }

    *(this->number_of_players) = ui->number_of_players->value();

    if(ui->Player_name_1->text() == ""){
        QString exception;
        exception = "نام بازیکن اول وارد نشده است!";
        throw exception;
    }
    if(ui->Player_name_2->text() == ""){
        QString exception;
        exception = "نام بازیکن دوم وارد نشده است!";
        throw exception;
    }
    if(ui->Player_name_3->text() == "" && *this->number_of_players > 2){
        QString exception;
        exception = "نام بازیکن سوم وارد نشده است!";
        throw exception;
    }
    if(ui->Player_name_4->text() == "" && *this->number_of_players == 4){
        QString exception;
        exception = "نام بازیکن چهارم وارد نشده است!";
        throw exception;
    }
    this->names->push_back(ui->Player_name_1->text());
    this->names->push_back(ui->Player_name_2->text());
    if(*number_of_players > 2){
        this->names->push_back(ui->Player_name_3->text());
        if(*number_of_players > 3){
            this->names->push_back(ui->Player_name_4->text());
        }
    }
    this->closed_by_button = true;
    this->close();
}

void SetPlayerDialog::on_number_of_players_valueChanged(int arg1)
{
    if(arg1 < 4){
        ui->message_6->setEnabled(false);
        ui->Player_name_4->setEnabled(false);
        if(arg1 < 3){
            ui->message_5->setEnabled(false);
            ui->Player_name_3->setEnabled(false);
        }
        else{
            ui->message_5->setEnabled(true);
            ui->Player_name_3->setEnabled(true);
        }
    }
    else{
        ui->Player_name_4->setEnabled(true);
        ui->message_6->setEnabled(true);
    }
}
