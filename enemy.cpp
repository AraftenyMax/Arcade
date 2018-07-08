#include "enemy.h"

Enemy::Enemy(int x, int y, QString name)
{
    this->x = x;
    this->y = y;
    this->name = name;
}

QString Enemy::serialize()
{
    return QString("%1, %2, %3").arg("Enemy", QString::number(x), QString::number(y));
}
