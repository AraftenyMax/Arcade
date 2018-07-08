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
    QList<Mesh*> Meshes;
    QList<Enemy*> Enemies;
    QList<Bonus*> Bonuses;
    QList<Weapon*> Weapons;
    QList<QGraphicsRectItem*> Markers;
    Player *player = nullptr;
private:
    int width, height;
};

#endif // MAP_H
