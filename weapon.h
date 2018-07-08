#ifndef WEAPON_H
#define WEAPON_H
#include <QString>


class Weapon
{
public:
    Weapon(int x, int y, QString type);
    QString serialize();
    static const int width = 10, height = 10;
private:
    int x, y;
    QString type;
};

#endif // WEAPON_H
