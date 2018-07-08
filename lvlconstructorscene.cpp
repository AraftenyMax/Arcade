#include "lvlconstructorscene.h"
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>

LvlConstructorScene::LvlConstructorScene()
{

}

void LvlConstructorScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    int x = event->scenePos().x();
    int y = event->scenePos().y();
    emit mousePressed(x, y);
}

