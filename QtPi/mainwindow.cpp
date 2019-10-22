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
template<typename CalcT>
void MainWindow::calculate(const CalcT &  calc, QString name)
{
    int steps = ui->leSteps->text().toInt();
    double result = calc.calculate(steps);
    QString textResult;
    ui->lblResult->setText(QString("Result: %1").arg(result,0,'g',14));
    qDebug()<<QString("%1(%2): %3").arg(name).arg(steps).arg(result);
}

void MainWindow::on_rbAtan_clicked()
{
    AtanCalculator calc;
    calculate(calc,"Atan");
}

void MainWindow::on_rbIntegrate_clicked()
{
    IntegrateCalculator calc;
    calculate(calc,"Integrate");
}
