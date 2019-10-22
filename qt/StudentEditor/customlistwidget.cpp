#include "customlistwidget.h"

#include<QMouseEvent>
#include <QDebug>

CustomListWidget::CustomListWidget()
{

}

void CustomListWidget::mousePressEvent(QMouseEvent *event)
{
    QModelIndex item = indexAt(event->pos());
    QListWidget::mousePressEvent(event);
    if (item.row()==-1) {
       emit currentRowRemoved();
    }


}
