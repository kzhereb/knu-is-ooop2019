#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>

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
    void on_btnAddImage_clicked();

    void on_lstImages_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);


private:
    Ui::MainWindow *ui;

    void setCurrentImage(const QString& filename);
};

#endif // MAINWINDOW_H
