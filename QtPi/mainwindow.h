#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "picalculator.h"
#include "models.h"

#include <QMainWindow>
#include <QHash>
#include <QStandardItemModel>

#include <memory>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_lswCalculators_currentTextChanged(const QString &currentText);

private:
    Ui::MainWindow *ui;

    QHash<QString, std::shared_ptr<PiCalculator>> mapCalc;

    std::shared_ptr<Models> models;

    void addCalculators();
    void calculate(const QString& name);
    void addResultToTable(const QString& name, int steps, double result);
};

#endif // MAINWINDOW_H
