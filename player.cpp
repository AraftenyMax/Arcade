#include "player.h"
#include <QGraphicsRectItem>
#include <QString>
#include <QKeyEvent>
#include <QRect>

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
    int oldX = currentX, oldY = currentY;
    switch(event->key()){
            case Qt::Key_Up:{
                setPos(x(), y() - 10);
                currentY -= 10;
                break;
            }
            case Qt::Key_Down:{
                setPos(x(), y() + 10);
                currentY += 10;
                break;
            }
            case Qt::Key_Left:{
                setPos(x() - 10, y());
                currentX -= 10;
                break;
            }
            case Qt::Key_Right:{
                setPos(x() + 10, y());
                currentX += 10;
                break;
            }
    }
    emit onKeyPressed("move", oldX, oldY, currentX, currentY);
}

QString Player::serialize()
{
    return QString("%1, %2, %3").arg("Player", QString::number(x()), QString::number(y()));
}
