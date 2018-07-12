#include "player.h"
#include <QGraphicsRectItem>
#include <QString>
#include <QKeyEvent>
#include <QRect>

#include "bonus.h"

Player::Player()
{

}

void Player::setCoords(int x, int y)
{
    currentX = x;
    currentY = y;
}

void Player::keyPressEvent(QKeyEvent *event)
{
    int newX = currentX, newY = currentY;
    int oldX = currentX, oldY = currentY;
    switch(event->key()){
            case Qt::Key_Up:{
                newY -= speed;
                break;
            }
            case Qt::Key_Down:{
                newY += speed;
                break;
            }
            case Qt::Key_Left:{
                newX -= speed;
                break;
            }
            case Qt::Key_Right:{
                newX += speed;
                break;
            }
    }
    emit onKeyPressed("move", oldX, oldY, newX, newY);
}

bool Player::decreaseHP()
{
    healthPoints -= 20;
    if(healthPoints <= 0)
        return true;
    return false;
}

void Player::pickUpBonus(Bonus *b)
{
    if (b->getType() == "HealthBonus")
        healthPoints += b->getValue();
    else if (b->getType() == "AttackBonus")
        attackPoints += b->getValue();
}

void Player::move(int xDiff, int yDiff)
{
    currentX += xDiff;
    currentY += yDiff;
    setPos(x() + xDiff, y() + yDiff);
}

QString Player::serialize()
{
    return QString("%1, %2, %3").arg("Player", QString::number(x()), QString::number(y()));
}
