#include "enemy.h"
#include "math.h"

#include <QPair>

Enemy::Enemy()
{

}

void Enemy::makeAgro()
{
    isAgro = true;
}

bool Enemy::isItAgro()
{
    return isAgro;
}

void Enemy::setCoords(int x, int y)
{
    currentX = x;
    currentY = y;
}

QPair<int, int> Enemy::getCoords()
{
    return QPair<int, int>(currentX, currentY);
}

void Enemy::move(int xCeil, int yCeil)
{
    currentX += xCeil;
    currentY += yCeil;
    setPos(x() + xCeil, y() + yCeil);
}


bool Enemy::isPlayerNear(int playerX, int playerY)
{
    return sqrt(pow(playerX - this->rect().x(), 2) + pow(playerY - this->rect().y(), 2)) <= agroRange ? true : false;
}

QString Enemy::serialize()
{
    return QString("%1, %2, %3").arg("Enemy", QString::number(x()), QString::number(y()));
}
