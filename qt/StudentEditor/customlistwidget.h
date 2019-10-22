#ifndef CUSTOMLISTWIDGET_H
#define CUSTOMLISTWIDGET_H

#include <QListWidget>

class CustomListWidget : public QListWidget
{
    Q_OBJECT
public:
    CustomListWidget(QWidget* parent):QListWidget(parent) {}
    CustomListWidget();
signals:
    void currentRowRemoved();
protected:
    void mousePressEvent(QMouseEvent *event) override;

};

#endif // CUSTOMLISTWIDGET_H
