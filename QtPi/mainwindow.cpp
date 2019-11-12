#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "picalculator.h"

#include <QDebug>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    models = std::make_shared<Models>();

    ui->tblResults->setModel(models->getModel());
    ui->tblResults->setColumnWidth(0,120);
    ui->tblResults->sortByColumn(0,Qt::SortOrder::AscendingOrder);


    addCalculators();
    ui->spinSteps->setFocus();
}

MainWindow::~MainWindow()
{
    delete ui;
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

void MainWindow::calculate(const QString& name)
{
    std::shared_ptr<PiCalculator> calc = mapCalc[name];
    int steps = ui->spinSteps->value();
    double result = calc->calculate(steps);
    QString textResult;
    //ui->lblResult->setText(QString("Result: %1").arg(result,0,'g',14));
    addResultToTable(name, steps, result);
    int digits = ui->spinDigits->value();
    qDebug()<<QString("%1(%2): %3").arg(name).arg(steps).arg(result,0,'g',digits);
}

void MainWindow::addResultToTable(const QString& name, int steps, double result)
{
    int digits = ui->spinDigits->value();
    models->addResult(name,steps,result,digits);


    ui->tblResults->setSortingEnabled(true);
}

void MainWindow::on_lswCalculators_currentTextChanged(const QString &currentText)
{
    calculate(currentText);
}
