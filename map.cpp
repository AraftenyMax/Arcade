#include "map.h"
#include "enemy.h"
#include "mesh.h"
#include "player.h"
#include <QList>
#include <QDebug>
#include <QTimer>
#include <QHash>
#include <QPair>
#include <QTextStream>

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
    QTextStream out(stdout);
    int xPlayerCoord = playerX/10, yPlayerCoord = playerY/10, xEnemyCoord = enemyX/10, yEnemyCoord = enemyY/10;
    int H = height/10;
    int W = width/10;
    int d, x, y, k;
    int dx[4] = {1, 0, -1, 0};
    int dy[4] = {0, 1, 0, -1};
    bool stop;
    temp_map[getPair(xPlayerCoord, yPlayerCoord)] = BLANK;
    temp_map[getPair(xEnemyCoord, yEnemyCoord)] = 0;
    int way_container_len = W*H;
    int px[way_container_len], py[way_container_len];
    d = 0;
    do{
        stop = true;
        for(x = 0; x < W; ++x)
            for(y = 0; y < H; ++y){
                if(temp_map[getPair(x, y)] == WALL) continue;
                if(temp_map[getPair(x, y)] == d){
                for ( k = 0; k < 4; ++k ) {
                    int iy = y + dy[k], ix = x + dx[k];
                    if(iy >= 0 && iy < H && ix >= 0 && ix < W && temp_map[getPair(ix, iy)] == BLANK)
                    {
                        stop = false;
                        temp_map[getPair(ix, iy)] = d + 1;
                    }
                }
            }
            }
        d++;
    }while(!stop && temp_map[getPair(xPlayerCoord, yPlayerCoord)] == BLANK);
    if(temp_map[getPair(xPlayerCoord, yPlayerCoord)] == BLANK)
    {
        return;
    }
    len = temp_map[getPair(xPlayerCoord, yPlayerCoord)];
    x = xPlayerCoord;
    y = yPlayerCoord;
    d = len;
    while(d > 0){
        px[d] = x;
        py[d] = y;
        d--;
        for(int k = 0; k < 4; ++k)
        {
            int iy = y + dy[k], ix = x + dx[k];
            int point = temp_map[getPair(ix, iy)];
            if(iy >= 0 && iy < H && ix >= 0 && ix < W)
                if(point == d)
                {
                    x = x + dx[k];
                    y = y + dy[k];
                    break;
                }
        }
    }
    px[0] = xEnemyCoord;
    py[0] = yEnemyCoord;
    enemy->move(px[1]*10 - enemyX, py[1]*10 - enemyY);
    map[enemy->getCoords()] = Enemy::markerType;
    map[getPair(px[0], py[0])] = BLANK;
}

void Map::setPlayer(Player *p)
{
    if (player == nullptr)
    {
        player = p;
        connect(player, SIGNAL(onKeyPressed(QString,int,int, int, int)), this, SLOT(tryPerformAction(QString,int,int, int, int)));
    }
}

bool Map::isOutOfBounds(int x, int y)
{
    qDebug() << x << ":" << y;
    return (x > width && y > height);
}

void Map::tryPerformAction(QString action, int oldX, int oldY, int newX, int newY)
{
    if (action == "move")
    {
        qDebug() << "I'am going to be at " << newX << ":" << newY;
        int xDiff = newX - oldX, yDiff = newY - oldY;
        if(map[getPair(newX/10, newY/10)] == WALL || newX < 0 || newY < 0 || newX > width-10 || newY > height-10)
            return;
        map[getPair(oldX/10, oldY/10)] = BLANK;
        map[getPair(newX/10, newY/10)] = player->markerType;
        player->move(xDiff, yDiff);
    }
}
