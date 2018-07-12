#ifndef ENEMY_H
#define ENEMY_H
#include <QString>
#include <QGraphicsRectItem>
#include <QObject>
#include <QPair>


class Enemy: public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    Enemy();
    QString serialize();
    void makeAgro();
    bool isItAgro();
    void move(int xCeil, int yCeil);
    void setCoords(int x, int y);
    bool isPlayerNear(int playerX, int playerY);
    QPair<int, int> getCoords();
    int currentX, currentY;
    static const int markerType = -4;
    static const int width = 10, height = 10;
private:
    QString name;
    int HP, strength;
    bool isAgro;
    int agroRange = 50;
    int speed = 10;
};

#endif // ENEMY_H
