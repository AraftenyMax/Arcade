#ifndef CHOOSEWINDOW_H
#define CHOOSEWINDOW_H

#include <QMainWindow>

namespace Ui {
class ChooseWindow;
}

class ChooseWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ChooseWindow(QWidget *parent = 0);
    ~ChooseWindow();

private slots:
    void on_lvl1_clicked();

    void on_lvl2_clicked();

    void on_lvl3_clicked();

    void on_loadLevel_clicked();

private:
    Ui::ChooseWindow *ui;
};

#endif // CHOOSEWINDOW_H
