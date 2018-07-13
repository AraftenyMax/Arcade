#include "mainwindow.h"
#include "levelconstructor.h"
#include "choosewindow.h"
#include "ui_mainwindow.h"
#include "myrect.h"

#include <QCoreApplication>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_constructorButton_clicked()
{
    Map *map = new Map(1000, 1000);
    LevelConstructor *levelConstructor = new LevelConstructor();
    levelConstructor->setMap(map);
    levelConstructor->show();
}

void MainWindow::on_exitButton_clicked()
{
    QCoreApplication::quit();
}

void MainWindow::on_gameButton_clicked()
{
    ChooseWindow *w = new ChooseWindow();
    w->show();
}
