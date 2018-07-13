#include "choosewindow.h"
#include "playwindow.h"
#include "ui_choosewindow.h"

#include <QMessageBox>
#include <QFileDialog>


ChooseWindow::ChooseWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ChooseWindow)
{
    ui->setupUi(this);
}

ChooseWindow::~ChooseWindow()
{
    delete ui;
}

void ChooseWindow::on_lvl1_clicked()
{
    PlayWindow *w = new PlayWindow();
    w->show();
    w->startGame("G:/Development/build-Game-Desktop_Qt_5_10_1_MinGW_32bit-Debug/level1.csv");
    this->close();
}

void ChooseWindow::on_lvl2_clicked()
{

}

void ChooseWindow::on_lvl3_clicked()
{

}

void ChooseWindow::on_loadLevel_clicked()
{
    QFileDialog dialog;
    QString path = dialog.getOpenFileName(this, "Select file", "", tr("CSV (*csv)"));
    if (path.isEmpty())
    {
        QMessageBox msg;
        msg.setText("Map file empty. Please, choose another one.");
        msg.exec();
        return;
    }
    PlayWindow *w = new PlayWindow();
    w->show();
    w->startGame(path);
    this->close();
}
