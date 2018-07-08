#ifndef BONUS_H
#define BONUS_H
#include <QString>


class Bonus
{
public:
    Bonus(int x, int y, QString type);
    QString serialize();
    static const int width = 10, height = 10;
private:
    int x, y;
    QString type;
};

#endif // BONUS_H
