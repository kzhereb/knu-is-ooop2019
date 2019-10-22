#include "mainwindow.h"
#include "ui_mainwindow.h"


#include <QMouseEvent>
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

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    //qDebug()<<event->isAccepted();
    int currentRow = ui->lstStudents->currentRow();
    qDebug()<< currentRow;
    if (currentRow != -1) {
        ui->lstStudents->setCurrentRow(-1);
        ui->leName->clear();
        ui->leAge->setText("19");
        ui->leGroup->setText("K28");
        ui->leCourse->setText("2");

    }

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

void MainWindow::on_lstStudents_currentRowChanged(int currentRow)
{
    if (currentRow == -1) { // not selected
        qDebug()<<"No selected item";
        return;
    }
    Student student = students[currentRow];
    ui->leName->setText(student.getName().c_str());
    ui->leAge->setText(QString::number(student.getAge()));
    ui->leGroup->setText(student.getGroup().c_str());
    ui->leCourse->setText(QString::number(student.getCourse()));
}

void MainWindow::on_btnEdit_clicked()
{
    int currentRow = ui->lstStudents->currentRow();
    if (currentRow == -1) { return;}
    Student& student = students[currentRow];
    student.setName(ui->leName->text().toUtf8().constData());
    student.setAge(ui->leAge->text().toInt());
    student.setGroup(ui->leGroup->text().toUtf8().constData());
    student.setCourse(ui->leCourse->text().toInt());
    QString display_name = QString("%1: %2 course, %3").arg(student.getName().c_str()).arg(student.getCourse()).arg(student.getGroup().c_str());

    ui->lstStudents->currentItem()->setText(display_name);

}
