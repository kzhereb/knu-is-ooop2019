#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "picalculator.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    addCalculators();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_calculator_clicked(std::unique_ptr<PiCalculator> calc, QString name)
{
    int steps = ui->spinSteps->value();
    int precision = ui->spinDigits->value();
    double result = calc->calculate(steps);
    qDebug()<<name<<" "<<result;

    ui->lblResult->setText(QString("Result: %1").arg(result,0,'g',precision));

}

void MainWindow::on_rbAtan_clicked()
{
    on_calculator_clicked(std::make_unique<AtanCalculator>(), "Atan");
}


void MainWindow::on_rbIntegrate_clicked()
{
    on_calculator_clicked(std::make_unique<IntegrateCalculator>(), "Integrate");
}

void MainWindow::on_lswCalculators_currentTextChanged(const QString &currentText)
{
    if(currentText=="Atan") {
        on_calculator_clicked(std::make_unique<AtanCalculator>(), "Atan");
    } else if (currentText=="Integrate") {
        on_calculator_clicked(std::make_unique<IntegrateCalculator>(), "Integrate");
    } else {
        qDebug()<<"Unknown calculator: "<<currentText;
    }

}

void MainWindow::addCalculators()
{
    ui->lswCalculators->addItem("Atan");
    ui->lswCalculators->addItem("Integrate");


}
