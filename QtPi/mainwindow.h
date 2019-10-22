#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "picalculator.h"
#include <QMainWindow>
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
    void on_rbAtan_clicked();

    void on_rbIntegrate_clicked();

private:
    Ui::MainWindow *ui;

    void calculate( std::shared_ptr<PiCalculator> calc, QString name);
};

#endif // MAINWINDOW_H
