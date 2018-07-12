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
    int tempX = xCeil*10, tempY = yCeil*10;
    int xDiff, yDiff;
    if(tempX > x() && tempY == y())
    {
        xDiff = speed;
        yDiff = 0;
    } else if (tempX < x() && tempY == y())
    {
        xDiff = -speed;
        yDiff = 0;
    } else if (tempX == x() && tempY > y()){
        xDiff = 0;
        yDiff = speed;
    } else if (tempX == x() && tempY < y())
    {
        xDiff = 0;
        yDiff = -speed;
    } else if (tempX > x() && tempY > x())
    {
        xDiff = speed;
        yDiff = speed;
    } else if (tempX < x() && tempY < y())
    {
        xDiff = -speed;
        yDiff = -speed;
    } else if (tempX > x() && tempY < y())
    {
        xDiff = speed;
        yDiff = -speed;
    } else if (tempX < x() && tempY > y())
    {
        xDiff = -speed;
        yDiff = speed;
    }
    currentX += xDiff;
    currentY += yDiff;
    setPos(x() + xDiff, y() + yDiff);
}

bool Enemy::isPlayerNear(int playerX, int playerY)
{
    return sqrt(pow(playerX - this->rect().x(), 2) + pow(playerY - this->rect().y(), 2)) <= agroRange ? true : false;
}

QString Enemy::serialize()
{
    return QString("%1, %2, %3").arg("Enemy", QString::number(x()), QString::number(y()));
}
