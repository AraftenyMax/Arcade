#include "map.h"
#include "enemy.h"
#include "mesh.h"
#include "player.h"
#include <QList>
#include <QDebug>
#include <QTimer>
#include <QHash>
#include <QPair>

Map::Map(const int width, const int height)
{
    this->width = width;
    this->height = height;
    initMap();
}

void Map::moveEnemies()
{
    qDebug() << "Player: " << player->x() << ":" << player->y();
    qDebug() << "There are " << Enemies.length() << " enemies";
    int playerX = player->x();
    int playerY = player->y();
    foreach (Enemy *e, Enemies) {
        if (e->isPlayerNear(playerX, playerY))
        {
            qDebug() << "Enemy: " << e->x() << ":" << e->y();
            doYouKnowDaWay(e->x(), e->y(), playerX, playerY);
        }
    }

}

void Map::startWatching()
{
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(moveEnemies()));
    timer->start(1000);
}

QPair<int, int> Map::getPair(int x, int y)
{
    return QPair<int, int>(x, y);
}

void Map::initMap()
{
    for(int i = 0; i < width/10; i++)
        for(int j = 0; j < height/10; j++)
            map[getPair(i, j)] = BLANK;
}

void Map::copyMap()
{
    for(int i = 0; i < width/10; i++)
        for(int j = 0; j < height/10; j++)
            temp_map[getPair(i,j)] = map[getPair(i, j)];
}

void Map::doYouKnowDaWay(int enemyX, int enemyY, int playerX, int playerY)
{
    copyMap();
    int len;
    int H = height/10;
    int W = width/10;
    int dx[4] = {1, 0, -1, 0};
    int dy[4] = {0, 1, 0, -1};
    int way_container_len = W*H;
    int px[way_container_len], py[way_container_len];
    int d, x, k, y;
    bool stop;
    if(temp_map[getPair(playerX, playerY)] == WALL || temp_map[getPair(enemyX, enemyY)] == WALL)
    {
        qDebug() << "Couldn't find da way";
        return;
    }
    d = 0;
    temp_map[getPair(playerX, playerY)] = Player::markerType;
    do
    {
        stop = true;
        for(y = 0; y < H; ++y)
            for(x = 0; x < W; ++x)
                if(temp_map[getPair(y,x)] == d){
                    for(k = 0; k < 4; ++k){
                        int iy = y + dy[k], ix = x + dx[k];
                        if(iy >= 0 && iy < H && ix >= 0 && ix < W && temp_map[getPair(iy, ix)] == BLANK)
                        {
                            stop = false;
                            temp_map[getPair(iy, ix)] = d + 1;
                        }
                    }
                }
         d++;

    }while(!stop && temp_map[getPair(playerX, playerY)] == Player::markerType);
    len = temp_map[getPair(enemyX, enemyY)];
    x = enemyX;
    y = enemyY;
    d = len;
    while(d > 0){
        px[d] = x;
        py[d] = y;
        d--;
        for(k = 0; k < 4; ++k){
            int iy = y + dy[k], ix = x + dx[k];
            if(iy > 0 && iy < H && ix > 0 && ix < W && temp_map[getPair(iy, ix)] == d){
                x = x + dx[k];
                y = y + dy[k];
                break;
            }
        }
    }
    px[0] = playerX;
    py[0] = playerY;
    qDebug() << "Could go to " << playerX << ":" << playerY;
}

void Map::setPlayer(Player *p)
{
    if (player == nullptr)
    {
        player = p;
        connect(player, SIGNAL(onKeyPressed(QString,int,int)), this, SLOT(tryPerformAction(QString,int,int)));
    }
}

void Map::tryPerformAction(QString action, int x, int y)
{
    if (action == "move")
    {
        checkNearestEnemies(x, y);
    }
}

void Map::checkNearestMeshes(int enemyX, int enemyY)
{
    foreach(Mesh* m, Meshes)
    {

    }
}

void Map::checkNearestEnemies(int x, int y)
{
    foreach (Enemy* e, Enemies) {
        if(e->isPlayerNear(x, y)){
            e->makeAgro();
            doYouKnowDaWay(e->x(), e->y(), x, y);
        }
    }
}

void Map::checkNearestBonuses(int x, int y)
{

}

void Map::checkNearestWeapons(int x, int y)
{

}

void Map::checkBounds(int x, int y)
{

}
