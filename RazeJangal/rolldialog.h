#ifndef ROLLDIALOG_H
#define ROLLDIALOG_H

#include <QDialog>

namespace Ui {
class RollDialog;
}

class RollDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RollDialog(QWidget *parent = 0, int* first_roll = 0, int* second_roll = 0);
    ~RollDialog();
private slots:
    void on_Button_clicked();

private:
    int* first_roll;
    int* second_roll;
    Ui::RollDialog *ui;
};

#endif // ROLLDIALOG_H
