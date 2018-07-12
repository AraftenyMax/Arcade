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
    scene = new QGraphicsScene(this);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setFixedSize(width, height);
    scene->setSceneRect(0, 0, width, height);
    ui->graphicsView->setScene(scene);
    loadMap(testMap);
    drawMap();
    map->setScene(scene);
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
    int xCoord = x/10;
    int yCoord = y/10;
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
        map->map[Map::getPair(xCoord, yCoord)] = Mesh::markerType;
        map->Meshes.append(mesh);
        markers.append(mesh);
    }
    if("Enemy" == type){
        Enemy *enemy = new Enemy();
        enemy->setRect(x, y, Enemy::width, Enemy::height);
        enemy->setBrush(QBrush(Qt::red));
        enemy->setCoords(x, y);
        map->map[Map::getPair(xCoord, yCoord)] = Mesh::markerType;
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
        playerRect->setCoords(x, y);
        map->map[Map::getPair(xCoord, yCoord)] = Player::markerType;
        map->setPlayer(playerRect);
        markers.append(playerRect);
        return;
    }
    if ("HealthBonus" == type || "AttackBonus" == type)
    {
        Bonus *bonus = new Bonus();
        bonus->setRect(x, y, Bonus::width, Bonus::height);
        bonus->setBrush(QBrush(type == "HealthBonus" ? Qt::blue : Qt::cyan));
        bonus->setType(type);
        bonus->setCoords(x, y);
        map->Bonuses.append(bonus);
        map->map[Map::getPair(xCoord, yCoord)] = "HealthBonus" == type
                ? Bonus::markerHealthBonus : Bonus::markerAttackBonus;
        markers.append(bonus);
        return;
    }
}

void PlayWindow::drawMap()
{
    foreach (Enemy *e, map->Enemies) {
        scene->addItem(e);
    }
    foreach (Mesh *m, map->Meshes) {
        scene->addItem(m);
    }
    foreach (Bonus *b, map->Bonuses) {
        scene->addItem(b);
    }
    scene->addItem(map->player);
}

PlayWindow::~PlayWindow()
{
    delete ui;
}
