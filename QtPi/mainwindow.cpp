#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "picalculator.h"

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

void MainWindow::on_rbAtan_clicked()
{
    AtanCalculator calc;
    double result = calc.calculate(1000);
    qDebug()<<"Atan "<<result;

    ui->lblResult->setText(QString("Result: %1").arg(result));
}

void MainWindow::on_rbIntegrate_clicked()
{
    IntegrateCalculator calc;
    double result = calc.calculate(1000);
    qDebug()<<"Integrate "<<result;

    ui->lblResult->setText(QString("Result: %1").arg(result));
}
