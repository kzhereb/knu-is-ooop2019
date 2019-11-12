#ifndef PICALCULATORRESULT_H
#define PICALCULATORRESULT_H

#include <QDateTime>

struct PiCalculatorResult {
    QDateTime timestamp;
    QString name;
    int steps;
    double result;
    int digits;
};

#endif // PICALCULATORRESULT_H
