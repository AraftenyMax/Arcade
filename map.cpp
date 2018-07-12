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
    int xPlayerCeil = playerX/10, yPlayerCeil = playerY/10, xEnemyCeil = enemyX/10, yEnemyCeil = enemyY/10;
    int H = height/10;
    int W = width/10;
    int d, x, y, k;
    int dx[4] = {1, 0, -1, 0};
    int dy[4] = {0, 1, 0, -1};
    bool stop;
    temp_map[getPair(yPlayerCeil, xPlayerCeil)] = BLANK;
    temp_map[getPair(yEnemyCeil, xEnemyCeil)] = 0;
    int way_container_len = W*H;
    int px[way_container_len], py[way_container_len];
    d = 0;
    qDebug() << "Old map";
    for(int i = 0; i < W; i++){
        for(int j = 0; j < H; j++){
            out << temp_map[getPair(i, j)];
        }
        out << endl;}
    do{
        stop = true;
        for(y = 0; y < W; ++y)
            for(x = 0; x < H; ++x){
                if(temp_map[getPair(y, x)] == WALL) continue;
                if(temp_map[getPair(y, x)] == d){
                for ( k = 0; k < 4; ++k ) {
                    int iy = y + dy[k], ix = x + dx[k];
                    if(iy >= 0 && iy < H && ix >= 0 && ix < W && temp_map[getPair(iy, ix)] == BLANK)
                    {
                        int point = temp_map[getPair(iy, ix)];
                        if(point == WALL)
                            qDebug() << "Damn sir, it's wall!";
                        stop = false;
                        temp_map[getPair(iy, ix)] = d + 1;
                    }
                }
            }
            }
        d++;
    }while(!stop && temp_map[getPair(yPlayerCeil, xPlayerCeil)] == BLANK);
    if(temp_map[getPair(yPlayerCeil, xPlayerCeil)] == BLANK)
    {
        qDebug() << "Could not find da way";
        return;
    }
    qDebug() << "Marked map";
    for(int i = 0; i < W; i++){
        for(int j = 0; j < H; j++){
            out << temp_map[getPair(i, j)];
        }
        out << endl;
    }
    len = temp_map[getPair(yPlayerCeil, xPlayerCeil)];
    x = xPlayerCeil;
    y = yPlayerCeil;
    d = len;
    while(d > 0){
        px[d] = x;
        py[d] = y;
        d--;
        for(int k = 0; k < 4; ++k)
        {
            int iy = y + dy[k], ix = x + dx[k];
            int point = temp_map[getPair(iy, ix)];
            if(iy >= 0 && iy < H && ix >= 0 && ix < W)
                if(point == d)
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
