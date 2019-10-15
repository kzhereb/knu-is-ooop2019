#include "mainwindow.h"
#include "ui_mainwindow.h"



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

void MainWindow::on_btnAdd_clicked()
{
    qDebug()<<"Add clicked!";
    Student student;
    string name = ui->leName->text().toUtf8().constData();
    student.setName(name);
    int age = ui->leAge->text().toInt();
    student.setAge(age);
    string group =  ui->leGroup->text().toUtf8().constData();
    student.setGroup(group);
    int course = ui->leCourse->text().toInt();
    student.setCourse(course);
    students.push_back(student);

    QString display_name = QString("%1: %2 course, %3").arg(name.c_str()).arg(course).arg(group.c_str());
    ui->lstStudents->addItem(display_name);

}
