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
#include <QGraphicsScene>
#include <QMessageBox>

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
        int d = e->calculateDistance(playerX, playerY);
        if(d == 10)
        {
            if(player->decreaseHP()){
                QMessageBox *b = new QMessageBox;
                b->setText("Вы проиграли!");
                b->show();
                disconnect(moveEnemiesTimer, SIGNAL(timeout()), this, SLOT(moveEnemies()));
                emit finishGame();
            }
            emit onHpChanged(player->healthPoints);
            continue;
        }
        doYouKnowDaWay(e->currentX, e->currentY, playerX, playerY, e);
    }
}

void Map::startWatching()
{
    moveEnemiesTimer = new QTimer(this);
    connect(moveEnemiesTimer, SIGNAL(timeout()), this, SLOT(moveEnemies()));
    moveEnemiesTimer->start(1000);
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
    map[getPair(px[1], py[1])] = Enemy::markerType;
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
    return (x < 0 || y < 0 || x > width-10 || y > height-10);
}

void Map::tryPerformAction(QString action, int oldX, int oldY, int newX, int newY)
{
    if (action == "move")
    {
        int x = newX/10, y = newY/10;
        int xDiff = newX - oldX, yDiff = newY - oldY;
        int nextSquare = map[getPair(x, y)];
        if(nextSquare == WALL || isOutOfBounds(newX, newY))
            return;
        if(nextSquare == Bonus::markerHealthBonus || nextSquare == Bonus::markerAttackBonus)
        {
            QList<Bonus*>::iterator iter = Bonuses.begin();
            for(; iter != Bonuses.end(); ++iter)
            {
                Bonus *b = *iter;
                int bonusX = b->currentX/10, bonusY = b->currentY/10;
                if(bonusX == x && bonusY == y){
                    player->pickUpBonus(b);
                    emit onHpChanged(player->healthPoints);
                    Bonuses.erase(iter);
                    scene->removeItem(b);
                    break;
                }
            }
        }
        if(nextSquare == Enemy::markerType)
        {
            QList<Enemy*>::iterator iter = Enemies.begin();
            for(; iter != Enemies.end(); ++iter)
            {
                Enemy *e = *iter;
                int enemyX = e->currentX, enemyY = e->currentY;
                if(enemyX == newX && enemyY == newY){
                    if(!e->decreaseHP(player->attackPoints)){
                        scene->removeItem(e);
                        Enemies.erase(iter);
                        if(Enemies.length() == 0){

                        }
                    }else
                        return;
                }
            }
        }
        map[getPair(oldX/10, oldY/10)] = BLANK;
        map[getPair(x, y)] = player->markerType;
        player->move(xDiff, yDiff);
    }
}

void Map::setScene(QGraphicsScene *scene)
{
    this->scene = scene;
}
