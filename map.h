#ifndef MAP_H
#define MAP_H
#include "enemy.h"
#include "mesh.h"
#include "player.h"
#include "bonus.h"
#include "weapon.h"

#include <QList>
#include <QObject>
#include <QHash>
#include <QPair>
#include <QGraphicsRectItem>

class Map: public QObject
{
    Q_OBJECT
public:
    Map(int width, int height);
    void Draw();
    void Update();
    void checkNearestMeshes(int x, int y);
    void checkNearestEnemies(int x, int y);
    void checkNearestBonuses(int x, int y);
    void checkNearestWeapons(int x, int y);
    void checkBounds(int x, int y);
    void setPlayer(Player *p);
    void copyMap();
    void initMap();
    void startWatching();
    void doYouKnowDaWay(int enemyX, int enemyY, int playerX, int playerY);
    static QPair<int, int> getPair(int x, int y);
    QString direction;
    QList<Mesh*> Meshes;
    QList<Enemy*> Enemies;
    QList<Bonus*> Bonuses;
    QList<Weapon*> Weapons;
    QList<QGraphicsRectItem*> Markers;
    Player *player = nullptr;
    QHash<QPair<int, int>, int> map;
    static const int BLANK = -2;
signals:
    void onKeyPressed(QString action, int x, int y);
    void moveEnemiesTimeout();
public slots:
    void tryPerformAction(QString action, int x, int y);
    void moveEnemies();
private:
    const int WALL = Mesh::markerType;
    int width, height;
    int playerAgroDistance = 50;
    QHash<QPair<int, int>, int> temp_map;
};

#endif // MAP_H
