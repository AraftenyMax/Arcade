#include "playwindow.h"
#include "ui_playwindow.h"
#include "player.h"
#include "enemy.h"
#include "mesh.h"
#include "map.h"
#include "bonus.h"

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
        QStringList data = line.split(',');
        int x = data[1].toInt();
        int y = data[2].toInt();
        createGameObject(x, y, data[0]);
    }
    file.close();
    map->startWatching();
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
        Mesh *mesh = new Mesh();
        mesh->setRect(x, y, Mesh::width, Mesh::height);
        mesh->setBrush(QBrush(Qt::black));
        mesh->setX(x);
        mesh->setY(y);
        map->map[Map::getPair(x, y)] = Mesh::markerType;
        map->Meshes.append(mesh);
        markers.append(mesh);
    }
    if("Enemy" == type){
        Enemy *enemy = new Enemy();
        enemy->setRect(x, y, Enemy::width, Enemy::height);
        enemy->setX(x);
        enemy->setY(y);
        enemy->setBrush(QBrush(Qt::red));
        map->map[Map::getPair(x, y)] = Map::BLANK;
        map->Enemies.append(enemy);
        markers.append(enemy);
        return;
    }
    if("Player" == type){
        Player *playerRect = new Player();
        playerRect->setFlag(QGraphicsItem::ItemIsFocusable);
        playerRect->setRect(x, y, Player::width, Player::height);
        playerRect->setBrush(QBrush(Qt::green));
        playerRect->setFocus();
        playerRect->setX(x);
        playerRect->setY(y);
        map->map[Map::getPair(x, y)] = Player::markerType;
        map->setPlayer(playerRect);
        markers.append(playerRect);
        return;
    }
    if ("HealthBonus" == type || "AttackBonus" == type)
    {
        Bonus *bonus = new Bonus(x, y, type);
        map->Bonuses.append(bonus);
        map->map[Map::getPair(x, y)] = Map::BLANK;
        rect = new QGraphicsRectItem(x, y, Bonus::width, Bonus::height);
        rect->setBrush(QBrush(type == "HealthBonus" ? Qt::blue : Qt::cyan));
    }
    if ("Gun1" == type || "Gun2" == type)
    {
        Weapon *gun = new Weapon(x, y, type);
        map->Weapons.append(gun);
        map->map[Map::getPair(x, y)] = Map::BLANK;
        rect = new QGraphicsRectItem(x, y, Weapon::width, Weapon::height);
        rect->setBrush(QBrush(type == "Gun1" ? Qt::yellow : Qt::magenta));
    }
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
