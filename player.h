#ifndef PLAYER_H
#define PLAYER_H
#include <QGraphicsRectItem>
#include <QObject>
#include <QKeyEvent>

#include "bonus.h"
#include "bullet.h"

class Player : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    Player();
    QString serialize();
    void keyPressEvent(QKeyEvent *event);
    void setCoords(int x, int y);
    void move(int xDiff, int yDiff);
    bool decreaseHP();
    void pickUpBonus(Bonus *b);
    static const int width = 10, height = 10;
    static const int markerType = -3;
    int currentX, currentY;
signals:
    void onKeyPressed(QString action, int oldX, int oldY, int newX, int newY);
    void onFireBullet(Bullet *b, QString direction, int startX, int startY);
private:
    int attackPoints = 20;
    int healthPoints = 100;
    int speed = 10;
    QString name;
};

#endif // PLAYER_H
