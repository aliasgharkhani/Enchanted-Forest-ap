#ifndef MAPEDITOR_H
#define MAPEDITOR_H

#include <QMainWindow>

namespace Ui {
class MapEditor;
}

class MapEditor : public QMainWindow
{
    Q_OBJECT

public:
    explicit MapEditor(QWidget *parent = 0);
    ~MapEditor();

private:
    Ui::MapEditor *ui;
};

#endif // MAPEDITOR_H
