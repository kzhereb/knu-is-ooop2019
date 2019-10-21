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
    int steps = ui->leSteps->text().toInt();
    AtanCalculator calc;
    double result = calc.calculate(steps);
    QString textResult;
    ui->lblResult->setText(QString("Result: %1").arg(result,0,'g',14));
    qDebug()<<QString("Atan(%1): %2").arg(steps).arg(result);
}

void MainWindow::on_rbIntegrate_clicked()
{
    int steps = ui->leSteps->text().toInt();
    IntegrateCalculator calc;
    double result = calc.calculate(steps);
    ui->lblResult->setText(QString("Result: %1").arg(result,0,'g',14));
    qDebug()<<QString("Integrate(%1): %2").arg(steps).arg(result);
}
