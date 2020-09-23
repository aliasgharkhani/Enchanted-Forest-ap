#ifndef SETPLAYERDIALOG_H
#define SETPLAYERDIALOG_H

#include <QDialog>
#include <razejangal.h>

namespace Ui {
class SetPlayerDialog;
}

class SetPlayerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SetPlayerDialog(QWidget *parent = 0, int* number_of_players = 0, std::vector<QString>* names = 0);
    ~SetPlayerDialog();

private slots:
    void on_Button_clicked();

    void on_number_of_players_valueChanged(int arg1);

private:
    bool closed_by_button;
    std::vector<QString>* names;
    int* number_of_players;
    Ui::SetPlayerDialog *ui;
};

#endif // SETPLAYERDIALOG_H
