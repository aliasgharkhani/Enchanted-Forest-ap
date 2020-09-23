#include <QtWidgets>
#include "mainwindow.h"
#include "dragwidget.h"

DragWidget::DragWidget(QWidget *parent)
    : QFrame(parent)
{
    setMinimumSize(200, 200);
    setFrameStyle(QFrame::Sunken | QFrame::StyledPanel);
    setAcceptDrops(true);
    show_position = new QLabel(this);
    show_position->move(1050, -20);
    show_position->setFixedHeight(101);
    show_position->setFixedWidth(111);
    show_position->setText("شماره خونه : _\nمولفه اول : _\nمولفه دوم : _");
    show_position->setStyleSheet("font-family: 0 Nazanin; background-color:rgb(239, 41, 41) ");
    show_position->show();


//    boatIcon = new QLabel(this);
//    boatIcon->setPixmap(QPixmap("/home/ali/project/RazeJangal/PNG/Blue.png"));
//    boatIcon->move(10, 10);
//    boatIcon->show();
//    boatIcon->setAttribute(Qt::WA_DeleteOnClose);

//    QLabel *carIcon = new QLabel(this);
//    carIcon->setPixmap(QPixmap("/home/ali/Qt/drop_drag/car.png"));
//    carIcon->move(100, 10);
//    carIcon->show();
//    carIcon->setAttribute(Qt::WA_DeleteOnClose);

//    QLabel *houseIcon = new QLabel(this);
//    houseIcon->setPixmap(QPixmap("/home/ali/Qt/drop_drag/house.png"));
//    houseIcon->move(10, 80);
//    houseIcon->show();
//    houseIcon->setAttribute(Qt::WA_DeleteOnClose);
}

void DragWidget::dragEnterEvent(QDragEnterEvent *event)
{

    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
        if (event->source() == this) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else {
            event->acceptProposedAction();
        }
    } else {
        event->ignore();
    }
}

void DragWidget::dragMoveEvent(QDragMoveEvent *event)
{

    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
        if (event->source() == this) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else {
            event->acceptProposedAction();
        }
    } else {
        event->ignore();
    }
}

void DragWidget::dropEvent(QDropEvent *event)
{
    if ((event->pos() - this->dragStartPosition).manhattanLength()
             < QApplication::startDragDistance())
            return;
    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
        QByteArray itemData = event->mimeData()->data("application/x-dnditemdata");
        QDataStream dataStream(&itemData, QIODevice::ReadOnly);

        QPixmap pixmap;
        QPoint offset;
        QString cell_number;
        QString cell_color;
        dataStream >> pixmap >> offset >> cell_number >> cell_color;

        greencells[(cell_number.toInt()) - 1] = new QLabel(this);
        greencells[(cell_number.toInt()) - 1]->setPixmap(pixmap);
        greencells[(cell_number.toInt()) - 1]->move(event->pos() - offset);
        greencells[(cell_number.toInt()) - 1]->setAccessibleName(cell_number);
        greencells[(cell_number.toInt()) - 1]->setObjectName(cell_color);
        greencells[(cell_number.toInt()) - 1]->show();

        greencells[(cell_number.toInt()) - 1]->setAttribute(Qt::WA_DeleteOnClose);

        if (event->source() == this) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else {
            event->acceptProposedAction();
        }
    } else {
        event->ignore();
    }
}

void DragWidget::mousePressEvent(QMouseEvent *event)
{

    if (event->button() == Qt::LeftButton)
            this->dragStartPosition = event->pos();

    QLabel *child = static_cast<QLabel*>(childAt(event->pos()));
    if (!child)
        return;

    QPixmap pixmap = *child->pixmap();
    QString cell_number = child->accessibleName();
    QString cell_color = child->objectName();
    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);
    dataStream << pixmap << QPoint(event->pos() - child->pos()) << cell_number << cell_color;
    this->current_cell_number = cell_number.toInt();
    QMimeData *mimeData = new QMimeData;
    mimeData->setData("application/x-dnditemdata", itemData);

    show_position->setText("شماره خونه : " + child->accessibleName() + "\n" + "مولفه اول : " + QString::number(child->pos().x()) + "\n" + "مولفه دوم : " + QString::number(child->pos().y()));



    QDrag *drag = new QDrag(this);

    drag->setMimeData(mimeData);
    drag->setPixmap(pixmap);
    drag->setObjectName(cell_color);
    drag->setHotSpot(event->pos() - child->pos());

    QPixmap tempPixmap = pixmap;
    QPainter painter;
    painter.begin(&tempPixmap);
    painter.fillRect(pixmap.rect(), QColor(127, 127, 127, 127));
    painter.end();

    child->setPixmap(tempPixmap);

    if (drag->exec(Qt::CopyAction | Qt::MoveAction, Qt::CopyAction) == Qt::MoveAction) {
        child->close();
    } else {
        child->show();
        child->setPixmap(pixmap);
    }
}
