#ifndef MODELS_H
#define MODELS_H

#include <QStandardItemModel>

class Models
{
public:
    Models();
    QAbstractItemModel* getModel();
    void addResult(QString name, int steps, double result, int digits);
private:
    QStandardItemModel * model;
};

#endif // MODELS_H
