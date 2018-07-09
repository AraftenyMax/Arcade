#ifndef MAP_H
#define MAP_H
#include "enemy.h"
#include "mesh.h"
#include "player.h"
#include "bonus.h"
#include "weapon.h"

#include <QList>
#include <QGraphicsRectItem>

class Map
{
public:
    Map(int width, int height);
    void Draw();
    void Update();
    void checkNearestMeshes();
    void checkNearestEnemies();
    void checkNearestBonuses();
    void checkNearestWeapons();
    void checkBounds();
    QList<Mesh*> Meshes;
    QList<Enemy*> Enemies;
    QList<Bonus*> Bonuses;
    QList<Weapon*> Weapons;
    QList<QGraphicsRectItem*> Markers;
    Player *player = nullptr;
signals:
    void onKeyPressed(QString action, int x, int y);
public slots:
    void tryPerformAction(QString action, int x, int y);
private:
    int width, height;
};

#endif // MAP_H
