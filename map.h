#ifndef MAP_H
#define MAP_H
#include "enemy.h"
#include "mesh.h"
#include "player.h"
#include "bonus.h"

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
    void checkBounds(int x, int y);
    void setPlayer(Player *p);
    void copyMap();
    void initMap();
    void setScene(QGraphicsScene *scene);
    void startWatching();
    bool isOutOfBounds(int x, int y);
    void doYouKnowDaWay(int enemyX, int enemyY, int playerX, int playerY, Enemy *enemy);
    static QPair<int, int> getPair(int x, int y);
    QString direction;
    QList<Mesh*> Meshes;
    QList<Enemy*> Enemies;
    QList<Bonus*> Bonuses;
    QList<QGraphicsRectItem*> Markers;
    Player *player = nullptr;
    QGraphicsScene *scene;
    QHash<QPair<int, int>, int> map;
    static const int BLANK = -2;
signals:
    void onKeyPressed(QString action, int oldX, int oldY, int newX, int newY);
    void moveEnemiesTimeout();
    void finishGame();
    void onHpChanged(int Hp);
public slots:
    void tryPerformAction(QString action, int oldX, int oldY, int newX, int newY);
    void moveEnemies();
private:
    QTimer *moveEnemiesTimer;
    const int WALL = Mesh::markerType;
    int width, height;
    int playerAgroDistance = 50;
    QHash<QPair<int, int>, int> temp_map;
};

#endif // MAP_H
