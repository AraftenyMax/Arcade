#ifndef PLAYER_H
#define PLAYER_H
#include <QGraphicsRectItem>
#include <QObject>
#include <QKeyEvent>

class Player : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    Player();
    QString serialize();
    void keyPressEvent(QKeyEvent *event);
    void setCoords(int x, int y);
    void move(int xDiff, int yDiff);
    static const int width = 10, height = 10;
    static const int markerType = -3;
    int currentX, currentY;
signals:
    void onKeyPressed(QString action, int oldX, int oldY, int newX, int newY);
private:
    int healthPoints = 100;
    int speed = 10;
    QString name;
};

#endif // PLAYER_H
