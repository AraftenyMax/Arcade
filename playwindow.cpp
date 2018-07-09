#include "playwindow.h"
#include "ui_playwindow.h"
#include "player.h"
#include "enemy.h"
#include "mesh.h"
#include "map.h"
#include "bonus.h"
#include "playermarker.h"

#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QMessageBox>
#include <QDebug>

PlayWindow::PlayWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PlayWindow)
{
    ui->setupUi(this);
    map = new Map(width, height);
    scene = new QGraphicsScene();
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setFixedSize(width, height);
    scene->setSceneRect(0, 0, width, height);
    ui->graphicsView->setScene(scene);
    loadMap(testMap);
    drawMap();
}

void PlayWindow::loadMap(QString path)
{
    QFile file(path);
    QTextStream in(&file);
    file.open(QIODevice::ReadWrite);
    while(!in.atEnd())
    {
        QString line = in.readLine();
        qDebug() << line;
        QStringList data = line.split(',');
        int x = data[1].toInt();
        int y = data[2].toInt();
        createGameObject(x, y, data[0]);
    }
    file.close();
}

void PlayWindow::createGameObject(int x, int y, QString type)
{
    QGraphicsRectItem *rect;
    if (type == "")
    {
        QMessageBox msg;
        msg.setText("Choose unit to place first");
        msg.exec();
        return;
    }
    if("Mesh" == type){
        Mesh *mesh = new Mesh(x, y);
        map->Meshes.append(mesh);
        rect = new QGraphicsRectItem(x, y, Mesh::width, Mesh::height);
        rect->setBrush(QBrush(Qt::black));
    }
    if("Enemy" == type){
        Enemy *enemy = new Enemy(x, y, type);
        map->Enemies.append(enemy);
        rect = new QGraphicsRectItem(x, y, Enemy::width, Enemy::height);
        rect->setBrush(QBrush(Qt::red));
    }
    if("Player" == type){
        if (map->player != nullptr)
        {
            QMessageBox msg;
            msg.setText("You have created player already.");
            msg.exec();
            return;
        }
        Player *player = new Player(x, y);
        map->player = player;
        PlayerMarker *playerRect = new PlayerMarker();
        playerRect->setFlag(QGraphicsItem::ItemIsFocusable);
        playerRect->setRect(x, y, Player::width, Player::height);
        playerRect->setBrush(QBrush(Qt::green));
        playerRect->setFocus();
        markers.append(playerRect);
        connect(playerRect, SIGNAL(onKeyPress(QString, int, int)), map, SLOT(chooseAction(QString,int,int)));
        return;
    }
    if ("HealthBonus" == type || "AttackBonus" == type)
    {
        Bonus *bonus = new Bonus(x, y, type);
        map->Bonuses.append(bonus);
        rect = new QGraphicsRectItem(x, y, Bonus::width, Bonus::height);
        rect->setBrush(QBrush(type == "HealthBonus" ? Qt::blue : Qt::cyan));
    }
    if ("Gun1" == type || "Gun2" == type)
    {
        Weapon *gun = new Weapon(x, y, type);
        map->Weapons.append(gun);
        rect = new QGraphicsRectItem(x, y, Weapon::width, Weapon::height);
        rect->setBrush(QBrush(type == "Gun1" ? Qt::yellow : Qt::magenta));
    }
    markers.append(rect);
}

void PlayWindow::drawMap()
{
    foreach(QGraphicsRectItem *rect, markers)
        scene->addItem(rect);
}

PlayWindow::~PlayWindow()
{
    delete ui;
}
