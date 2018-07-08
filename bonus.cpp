#include "bonus.h"

Bonus::Bonus(int x, int y, QString type)
{
    this->x = x;
    this->y = y;
    this->type = type;
}

QString Bonus::serialize()
{
    return QString("%1, %2, %3").arg(type, QString::number(x), QString::number(y));
}
