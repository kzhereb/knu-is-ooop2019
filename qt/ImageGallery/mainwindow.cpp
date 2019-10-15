#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setCurrentImage(const QString& fileName)
{
    QPixmap pic(fileName);
    ui->lblCurrentImage->setPixmap(pic);
}

void MainWindow::on_btnAddImage_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open Image"), QString(), tr("Image Files (*.png *.jpg *.bmp)"));
    qDebug()<<fileName;
    setCurrentImage(fileName);

    QListWidgetItem * listItem = new QListWidgetItem(QIcon(fileName), fileName);
    listItem->setSizeHint( QSize(384,216) );
    ui->lstImages->addItem(listItem);
}

void MainWindow::on_lstImages_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    QString fileName = current->text();
    setCurrentImage(fileName);

}


