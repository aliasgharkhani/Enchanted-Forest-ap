#ifndef DRAGWIDGET_H
#define DRAGWIDGET_H

#include <QFrame>
#include <vector>
#include <QLabel>

class QDragEnterEvent;
class QDropEvent;

class DragWidget : public QFrame
{


public:
    int current_cell_number;
    QLabel *greencells[116];
    DragWidget(QWidget *parent = 0);
private:
    QPoint dragStartPosition;
    QLabel *show_position;
protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    void dropEvent(QDropEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
};

#endif // DRAGWIDGET_H
