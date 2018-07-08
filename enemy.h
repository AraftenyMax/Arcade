#ifndef ENEMY_H
#define ENEMY_H
#include <QString>


class Enemy
{
public:
    Enemy(int x, int y, QString name);
    QString serialize();
    static const int width = 10, height = 10;
private:
    QString name;
    int x, y, HP, strength;
};

#endif // ENEMY_H
