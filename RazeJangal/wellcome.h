#ifndef WELLCOME_H
#define WELLCOME_H

#include <QDialog>

namespace Ui {
class Wellcome;
}

class Wellcome : public QDialog
{
    Q_OBJECT

public:
    explicit Wellcome(QWidget *parent = 0);
    ~Wellcome();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Wellcome *ui;
};

#endif // WELLCOME_H
