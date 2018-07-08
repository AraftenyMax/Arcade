#include "levelconstructor.h"
#include "ui_levelconstructor.h"
#include "map.h"
#include "enemy.h"
#include "mesh.h"
#include "player.h"
#include "lvlconstructorscene.h"
#include "bonus.h"
#include "weapon.h"

#include <QDebug>
#include <QBrush>
#include <QString>
#include <QMessageBox>
#include <QStringList>
#include <QFileDialog>
#include <QDataStream>
#include <QDir>

LevelConstructor::LevelConstructor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LevelConstructor)
{
    ui->setupUi(this);
    map = new Map(200, 200);
    scene = new LvlConstructorScene();
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setFixedSize(width, height);
    scene->setSceneRect(0,0, width, height);
    connect(scene, SIGNAL(mousePressed(int,int)), this, SLOT(obtainCoordinates(int,int)));
    ui->graphicsView->setScene(scene);
}

LevelConstructor::~LevelConstructor()
{
    delete ui;
}

void LevelConstructor::on_MeshButton_clicked()
{
    mode = "Create";
    state = "Mesh";
}

void LevelConstructor::on_enemyButton_clicked()
{
    mode = "Create";
    state = "Enemy";
}

void LevelConstructor::on_playerButton_clicked()
{
    mode = "Create";
    state = "Player";
}

void LevelConstructor::on_healthBonus_clicked()
{
    mode = "Create";
    state = "HealthBonus";
}

void LevelConstructor::on_attackBonus_clicked()
{
    mode = "Create";
    state = "AttackBonus";
}

void LevelConstructor::on_gun1Button_clicked()
{
    mode = "Create";
    state = "Gun1";
}

void LevelConstructor::on_gun2Button_clicked()
{
    mode = "Create";
    state = "Gun2";
}

void LevelConstructor::on_saveButton_clicked()
{
    if (!map->player)
    {
        QMessageBox msg;
        msg.setText("Create player first");
        msg.exec();
    }
    QStringList *mapData = new QStringList();
    mapData->append(map->player->serialize());
    if (map->Meshes.length() != 0){
        foreach (Mesh *m, map->Meshes) {
            mapData->append(m->serialize());
        }
    }
    if(map->Enemies.length() != 0){
        foreach (Enemy *e, map->Enemies) {
            mapData->append(e->serialize());
        }
    }
    if (map->Bonuses.length() != 0){
        foreach (Bonus *b, map->Bonuses) {
            mapData->append(b->serialize());
        }
    }
    if (map->Weapons.length() != 0){
        foreach (Weapon *w, map->Weapons) {
            mapData->append(w->serialize());
        }
    }
    saveMap(mapData);
}

void LevelConstructor::setMap(Map *map)
{
    this->map = map;
}

void LevelConstructor::obtainCoordinates(int x, int y)
{
    if (mode == "Create")
        createObject(x, y);
    else if (mode == "Delete")
        deleteObject(x, y);
}

void LevelConstructor::loadMap()
{
    QFileDialog dialog;
    QString path = dialog.getOpenFileName(this, "Select file", "", tr("CSV (*csv)"));
    if (path.isEmpty())
    {
        QMessageBox msg;
        msg.setText("Map file empty. Please, choose another one.");
        msg.exec();
        return;
    }else{
        QFile file(path);
        if(!file.open(QIODevice::ReadOnly))
        {
            QMessageBox msg;
            msg.setText("Unable to open file.");
            msg.exec();
            return;
        }
        QTextStream in(&file);
        while(!in.atEnd())
        {
            QString line = in.readLine();
            QStringList data = line.split(',');
            state = data[0];
            int x = data[1].toInt();
            int y = data[2].toInt();
            createObject(x, y);
        }
    }
}

void LevelConstructor::saveMap(QStringList *mapData)
{
    QFileDialog dialog;
    dialog.setFileMode(QFileDialog::Directory);
    QString path = dialog.getSaveFileName(this, "Select directory", "", tr("CSV (*.csv)"));
    QFile file(path);
    if(file.open(QIODevice::ReadWrite))
    {
        QTextStream stream(&file);
        for (QStringList::Iterator it = mapData->begin(); it != mapData->end(); ++it)
            stream << *it << endl;
    }
}

void LevelConstructor::createObject(int x, int y)
{
    QGraphicsRectItem *rect;
    if (state == "")
    {
        QMessageBox msg;
        msg.setText("Choose unit to place first");
        msg.exec();
        return;
    }
    if("Mesh" == state){
        Mesh *mesh = new Mesh(x, y);
        map->Meshes.append(mesh);
        rect = new QGraphicsRectItem(x, y, Mesh::width, Mesh::height);
        rect->setBrush(QBrush(Qt::black));
    }
    if("Enemy" == state){
        Enemy *enemy = new Enemy(x, y, state);
        map->Enemies.append(enemy);
        rect = new QGraphicsRectItem(x, y, Enemy::width, Enemy::height);
        rect->setBrush(QBrush(Qt::red));
    }
    if("Player" == state){
        if (map->player != nullptr)
        {
            QMessageBox msg;
            msg.setText("You have created player already.");
            msg.exec();
            return;
        }
        Player *player = new Player(x, y);
        map->player = player;
        rect = new QGraphicsRectItem(x, y, Player::width, Player::height);
        rect->setBrush(QBrush(Qt::green));
    }
    if ("HealthBonus" == state || "AttackBonus" == state)
    {
        Bonus *bonus = new Bonus(x, y, state);
        map->Bonuses.append(bonus);
        rect = new QGraphicsRectItem(x, y, Bonus::width, Bonus::height);
        rect->setBrush(QBrush(state == "HealthBonus" ? Qt::blue : Qt::cyan));
    }
    if ("Gun1" == state || "Gun2" == state)
    {
        Weapon *gun = new Weapon(x, y, state);
        map->Weapons.append(gun);
        rect = new QGraphicsRectItem(x, y, Weapon::width, Weapon::height);
        rect->setBrush(QBrush(state == "Gun1" ? Qt::yellow : Qt::magenta));
    }
    map->Markers.append(rect);
    this->scene->addItem(rect);
}

void LevelConstructor::deleteObject(int x, int y)
{
    QPointF *point = new QPointF(x, y);
    foreach (QGraphicsRectItem *rect, map->Markers) {
        if(rect->contains(*point))
            scene->removeItem(rect);
    }
}

void LevelConstructor::on_loadMap_clicked()
{
    loadMap();
}

void LevelConstructor::on_deleteButton_clicked()
{
    mode = "Delete";
}
