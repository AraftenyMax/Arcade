#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_constructorButton_clicked();

    void on_exitButton_clicked();

    void on_gameButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
