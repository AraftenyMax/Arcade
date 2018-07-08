#ifndef LVLCONSTRUCTORSCENE_H
#define LVLCONSTRUCTORSCENE_H
#include <QGraphicsScene>
#include <QGraphicsRectItem>

class LvlConstructorScene : public QGraphicsScene
{
    Q_OBJECT
public:
    LvlConstructorScene();
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
signals:
    void mousePressed(int x, int y);
};

#endif // LVLCONSTRUCTORSCENE_H
