#include "levelconstructor.h"
#include "ui_levelconstructor.h"
#include "map.h"
#include "enemy.h"
#include "mesh.h"
#include "player.h"
#include "lvlconstructorscene.h"
#include "bonus.h"

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
    map = new Map(width, height);
    scene = new LvlConstructorScene();
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setFixedSize(width, height);
    ui->graphicsView->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    scene->setSceneRect(0, 0, width, height);
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
        qDebug() << path;
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
    qDebug() << x << ":" << y;
    QGraphicsRectItem *rect;
    x -= x%10;
    y -= y%10;

    foreach (QGraphicsRectItem* i, map->Markers) {
        if(i->rect().x() == x && y == i->rect().y())
            return;
    }

    if (state == "")
    {
        QMessageBox msg;
        msg.setText("Choose unit to place first");
        msg.exec();
        return;
    }
    if("Mesh" == state){
        Mesh *mesh = new Mesh();
        map->Meshes.append(mesh);
        mesh->setX(x);
        mesh->setY(y);
        mesh->setCoords(x, y);
        rect = new QGraphicsRectItem(x, y, Mesh::width, Mesh::height);
        mesh->setRect(x, y, Mesh::width, Mesh::height);
        rect->setBrush(QBrush(Qt::black));
    }
    if("Enemy" == state){
        Enemy *enemy = new Enemy();
        map->Enemies.append(enemy);
        enemy->setCoords(x, y);
        enemy->setX(x);
        enemy->setY(y);
        rect = new QGraphicsRectItem(x, y, Enemy::width, Enemy::height);
        enemy->setRect(x, y, Enemy::width, Enemy::height);
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
        Player *player = new Player();
        map->player = player;
        player->setX(x);
        player->setY(y);
        player->setCoords(x, y);
        rect = new QGraphicsRectItem(x, y, Player::width, Player::height);
        player->setRect(x, y, Player::width, Player::height);
        rect->setBrush(QBrush(Qt::green));
    }
    if ("HealthBonus" == state || "AttackBonus" == state)
    {
        Bonus *bonus = new Bonus();
        bonus->setType(state);
        bonus->setX(x);
        bonus->setY(y);
        bonus->setCoords(x, y);
        map->Bonuses.append(bonus);
        rect = new QGraphicsRectItem(x, y, Bonus::width, Bonus::height);
        bonus->setRect(x, y, Bonus::width, Bonus::height);
        rect->setBrush(QBrush(state == "HealthBonus" ? Qt::blue : Qt::cyan));
    }
    map->Markers.append(rect);
    this->scene->addItem(rect);
}

void LevelConstructor::deleteObject(int x, int y)
{
    QPointF *point = new QPointF(x, y);
    foreach (QGraphicsRectItem *rect, map->Markers)
        if(rect->contains(*point))
            scene->removeItem(rect);
}

void LevelConstructor::on_loadMap_clicked()
{
    loadMap();
}

void LevelConstructor::on_deleteButton_clicked()
{
    mode = "Delete";
}

void LevelConstructor::closeEvent(QCloseEvent *event)
{
    disconnect(scene, SIGNAL(mousePressed(int,int)), this, SLOT(obtainCoordinates(int,int)));
    delete map;
    delete scene;
    QWidget::closeEvent(event);
}
