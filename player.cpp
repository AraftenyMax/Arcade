#include "player.h"
#include <QGraphicsRectItem>
#include <QString>
#include <QKeyEvent>
#include <QRect>

Player::Player()
{

}

void Player::keyPressEvent(QKeyEvent *event)
{
    emit onKeyPressed("move", x(), y());
    switch(event->key()){
        case Qt::Key_Up:{
            setPos(x(), y() - 10);
            break;
        }
        case Qt::Key_Down:{
            setPos(x(), y() + 10);
            break;
        }
        case Qt::Key_Left:{
            setPos(x() - 10, y());
            break;
        }
        case Qt::Key_Right:{
            setPos(x() + 10, y());
            break;
        }
    }
}

QString Player::serialize()
{
    return QString("%1, %2, %3").arg("Player", QString::number(x()), QString::number(y()));
}
