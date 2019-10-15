#include "mainwindow.h"
#include "picalculator.h"
#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    IntegrateCalculator calc;
    qDebug()<<calc.calculate(100);

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
