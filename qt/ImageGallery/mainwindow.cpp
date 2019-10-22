#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QDebug>

#include <QSqlDriver>
#include <QSqlError>
#include <QSqlQuery>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initDb();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showEvent(QShowEvent *ev)
{
    QMainWindow::showEvent(ev);
    loadFromDb();
}

void MainWindow::setCurrentImage(const QString& fileName)
{
    QPixmap pic(fileName);
    ui->lblCurrentImage->setPixmap(pic);
}

void MainWindow::initDb()
{
    const QString DRIVER("QSQLITE");
    if(!QSqlDatabase::isDriverAvailable(DRIVER)) {
        qDebug()<<"SQLite not available";
        return;
    }
    QSqlDatabase db = QSqlDatabase::addDatabase(DRIVER);
    db.setDatabaseName("images.db");
    if(!db.open()) {
        qDebug() << "ERROR: " << db.lastError();
        return;
    }
    QSqlQuery query("CREATE TABLE images (id INTEGER PRIMARY KEY, path TEXT)");
    if(!query.isActive()) {
        qDebug() << "ERROR: " << query.lastError().text();
        return;
    }
    qDebug() << "File-based SQLite DB created (probably)";
}

void MainWindow::loadFromDb()
{
    QSqlQuery query;
    if(!query.exec("SELECT path FROM images")) {
      qDebug() << "ERROR loading: " << query.lastError().text();
    }
    if (!query.first()) {
        qDebug()<<"No results";
        return;
    }
    do {
        QString path = query.value(0).toString();
        qDebug()<<path;
        addImageToList(path);

    } while( query.next());
}

void MainWindow::saveToDb(const QString& path)
{
    QSqlQuery query;
    query.prepare("INSERT INTO images(path) VALUES(?)");
    query.addBindValue(path);
    if(!query.exec()) {
      qDebug() << "ERROR saving: " << query.lastError().text();
    }

}

void MainWindow::addImageToList(QString fileName)
{
    QListWidgetItem * listItem = new QListWidgetItem(QIcon(fileName), fileName);
    listItem->setSizeHint( QSize(384,216) );
    ui->lstImages->addItem(listItem);
}

void MainWindow::on_btnAddImage_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open Image"), QString(), tr("Image Files (*.png *.jpg *.bmp)"));
    qDebug()<<fileName;
    setCurrentImage(fileName);

    addImageToList(fileName);

    saveToDb(fileName);
}

void MainWindow::on_lstImages_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    QString fileName = current->text();
    setCurrentImage(fileName);

}


