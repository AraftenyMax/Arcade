#include "player.h"
#include <QGraphicsRectItem>
#include <QString>
#include <QKeyEvent>
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

void Player::keyPressEvent(QKeyEvent *event)
{

}

QString Player::serialize()
{
    return QString("%1, %2, %3").arg("Player", QString::number(x), QString::number(y));
}
