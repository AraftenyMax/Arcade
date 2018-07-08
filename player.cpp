#include "player.h"
#include <QGraphicsRectItem>
#include <QString>
#include <QRect>

Player::Player()
{

}

Player::Player(int x, int y)
{
    this->x = x;
    this->y = y;
    this->name = name;
}

QString Player::serialize()
{
    return QString("%1, %2, %3").arg("Player", QString::number(x), QString::number(y));
}
