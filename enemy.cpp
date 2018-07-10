#include "enemy.h"
#include "math.h"

Enemy::Enemy()
{

}

void Enemy::makeAgro()
{
    isAgro = true;
}

void Enemy::move(QString direction)
{
    if(direction == "up")
        setPos(x(), y() - speed);
    else if(direction == "down")
        setPos(x(), y() + speed);
    else if(direction == "left")
        setPos(x() - speed, y());
    else if(direction == "right")
        setPos(x() + speed, y());
}

bool Enemy::isPlayerNear(int playerX, int playerY)
{
    return sqrt(pow(playerX - x(), 2) + pow(playerY - y(), 2)) <= agroRange ? true : false;
}

QString Enemy::serialize()
{
    return QString("%1, %2, %3").arg("Enemy", QString::number(x()), QString::number(y()));
}
