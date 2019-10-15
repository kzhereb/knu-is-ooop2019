#include "mainwindow.h"
#include "picalculator.h"
#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    AtanCalculator calc;
    qDebug()<<"Atan "<<calc.calculate(1000);
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
