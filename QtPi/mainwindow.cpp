#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "picalculator.h"

#include <QDebug>
#include <QDateTime>

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

void MainWindow::on_calculator_clicked(std::shared_ptr<PiCalculator> calc, QString name)
{
    int steps = ui->spinSteps->value();
    int digits = ui->spinDigits->value();
    double result = calc->calculate(steps);
    qDebug()<<name<<" "<<result;

    //ui->lblResult->setText(QString("Result: %1").arg(result,0,'g',precision));
    addResultToTable(name, steps, result, digits);
}



void MainWindow::on_lswCalculators_currentTextChanged(const QString &currentText)
{
    on_calculator_clicked(mapCalc[currentText],currentText );
}

void MainWindow::addCalculators()
{
    mapCalc["Atan"] = std::make_shared<AtanCalculator>();
    mapCalc["Integrate"] = std::make_shared<IntegrateCalculator>();
    mapCalc["Monte Carlo"] = std::make_shared<MonteCarloCalculator>();
    mapCalc["Euler 2,3"] = std::make_shared<TwoAtanCalculator>(1,2,1,1,3,1);
    mapCalc["Machin 5,239"] = std::make_shared<TwoAtanCalculator>(1,5,4,1,239,-1);

    foreach(const QString &key, mapCalc.keys()) {
        ui->lswCalculators->addItem(key);
    }

}

void MainWindow::addResultToTable(const QString &name, int steps, double result, int digits)
{
    int rows = ui->tblResults->rowCount();
    ui->tblResults->setRowCount(rows+1);

//    QTableWidgetItem * itemPos = new QTableWidgetItem(QString::number(rows+1));
//    ui->tblResults->setItem(rows,0,itemPos);

    QString time = QDateTime::currentDateTime().toString();

    QTableWidgetItem * itemDT = new QTableWidgetItem(time);
    ui->tblResults->setItem(rows,0,itemDT);

    QTableWidgetItem* itemName = new QTableWidgetItem(name);
    ui->tblResults->setItem(rows,1,itemName);

    QTableWidgetItem* itemSteps = new QTableWidgetItem(QString::number(steps));
    ui->tblResults->setItem(rows,2,itemSteps);

    QTableWidgetItem* itemResult = new QTableWidgetItem(QString::number(result,'g',digits));
    ui->tblResults->setItem(rows,3,itemResult);

    QTableWidgetItem* itemDigits = new QTableWidgetItem(QString::number(digits));
    ui->tblResults->setItem(rows,4,itemDigits);

}
