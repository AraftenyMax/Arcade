#ifndef PLAYER_H
#define PLAYER_H
#include <QGraphicsRectItem>
#include <QObject>

class Player : QObject
{
    Q_OBJECT
public:
    Player();
    Player(int x, int y);
    QString serialize();
    static const int width = 10, height = 10;
private:
    int healthPoints = 100;
    int x, y;
    int visibleRange = 50;
    QString name;
    QRect *rect;
};

#endif // PLAYER_H
