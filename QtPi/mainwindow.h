#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "picalculator.h"

#include <QMainWindow>
#include <QHash>

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

    QHash<QString,std::shared_ptr<PiCalculator>> mapCalc;

    void addCalculators();
    void addResultToTable(const QString& name, int steps, double result, int digits);
    void on_calculator_clicked(std::shared_ptr<PiCalculator> calc, QString name);
};

#endif // MAINWINDOW_H
