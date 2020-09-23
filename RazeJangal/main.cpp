#include "razejangal.h"
#include <QApplication>
#include <QMessageBox>

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    try{
        RazeJangal w(0);

        w.show();
        w.start_game();
    }
    catch(QString exception){
        QMessageBox::warning(0,"خطا",exception, QMessageBox::Ok);
    }

    return a.exec();
}


