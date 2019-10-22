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


protected:
    void mousePressEvent(QMouseEvent *event) override;

private slots:
    void on_btnAdd_clicked();

    void on_lstStudents_currentRowChanged(int currentRow);

    void on_btnEdit_clicked();

    void on_lstStudents_clicked(const QModelIndex &index);

    void on_lstStudents_currentRowRemoved();
    void on_deleteAction_triggered(bool checked);

private:
    Ui::MainWindow *ui;
    std::vector<Student> students;
    void initActions();

    void clearCurrentStudent();
};

#endif // MAINWINDOW_H
