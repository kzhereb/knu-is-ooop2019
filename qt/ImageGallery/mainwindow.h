#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>

#include <QSqlDatabase>

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
      void showEvent(QShowEvent *ev) override;

private slots:
    void on_btnAddImage_clicked();

    void on_lstImages_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);


private:
    Ui::MainWindow *ui;



    void setCurrentImage(const QString& filename);

    void initDb();
    void loadFromDb();
    void saveToDb(const QString& path);
    void addImageToList(QString fileName);
};

#endif // MAINWINDOW_H
