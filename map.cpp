#include "map.h"
#include "enemy.h"
#include "mesh.h"
#include "player.h"
#include <QList>
#include <QDebug>
#include <QTimer>
#include <QHash>
#include <QPair>

Map::Map(int width, int height)
{
    this->width = width;
    this->height = height;
    initMap();
}

void Map::moveEnemies()
{
    int playerX = player->currentX;
    int playerY = player->currentY;
    foreach (Enemy *e, Enemies) {
        if(!e->isItAgro())
            if(e->isPlayerNear(playerX, playerY))
                e->makeAgro();
            else continue;
        qDebug() << "Enemy: " << e->currentX << ":" << e->currentY;
        doYouKnowDaWay(e->currentX, e->currentY, playerX, playerY, e);
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

void Map::doYouKnowDaWay(int enemyX, int enemyY, int playerX, int playerY, Enemy *enemy)
{
    copyMap();
    int len;
    int xPlayerCeil = playerX/10, yPlayerCeil = playerY/10, xEnemyCeil = enemyX/10, yEnemyCeil = enemyY/10;
    int H = height/10;
    int W = width/10;
    int d, x, y, k;
    int dx[4] = {1, 0, -1, 0};
    int dy[4] = {0, 1, 0, -1};
    bool stop;
    temp_map[getPair(xPlayerCeil, yPlayerCeil)] = BLANK;
    int way_container_len = W*H;
    int px[way_container_len], py[way_container_len];

    d = 0;
    temp_map[getPair(xEnemyCeil, yEnemyCeil)] = 0;
    do{
        stop = true;
        for(y = 0; y < W; ++y)
            for(x = 0; x < H; ++x)
                for ( k = 0; k < 4; ++k ) {
                if(temp_map[getPair(y, x)] == d)
                {
                    int iy = y + dy[k], ix = x + dx[k];
                    if(iy >= 0 && iy < H && ix >= 0 && ix < W && temp_map[getPair(iy, ix)] == BLANK)
                    {
                        stop = false;
                        temp_map[getPair(iy, ix)] = d + 1;
                    }
                }
            }
        d++;
    }while(!stop && temp_map[getPair(xPlayerCeil, yPlayerCeil)] == BLANK);
    if(temp_map[getPair(xPlayerCeil, yPlayerCeil)] == BLANK)
    {
        qDebug() << "Could not find da way";
        return;
    }
    len = temp_map[getPair(xPlayerCeil, yEnemyCeil)];
    x = xPlayerCeil;
    y = yPlayerCeil;
    while(d > 0){
        px[d] = x;
        py[d] = y;
        d--;
        for(int k = 0; k < 4; ++k)
        {
            int iy = y + dy[k], ix = x + dx[k];
            if(iy >= 0 && iy < H && ix >= 0 && ix < W && map[getPair(iy, ix)] == d)
            {
                x = x + dx[k];
                y = y + dy[k];
                break;
            }
        }
    }
    px[0] = xEnemyCeil;
    py[0] = yEnemyCeil;
    enemy->move(px[1]*10 - enemyX, py[1]*10 - enemyY);
    map[enemy->getCoords()] = BLANK;
}

void Map::setPlayer(Player *p)
{
    if (player == nullptr)
    {
        player = p;
        connect(player, SIGNAL(onKeyPressed(QString,int,int, int, int)), this, SLOT(tryPerformAction(QString,int,int, int, int)));
    }
}

void Map::tryPerformAction(QString action, int oldX, int oldY, int newX, int newY)
{
    if (action == "move")
    {
        map[getPair(oldX/10, oldY/10)] = BLANK;
        map[getPair(newX/10, newY/10)] = player->markerType;
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
            doYouKnowDaWay(e->x(), e->y(), x, y, e);
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
