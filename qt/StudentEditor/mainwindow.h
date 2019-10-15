#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "student.h"

#include <QMainWindow>

#include <vector>

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
    void on_btnAdd_clicked();

private:
    Ui::MainWindow *ui;
    std::vector<Student> students;
};

#endif // MAINWINDOW_H
