#include "bonus.h"

Bonus::Bonus()
{
}

void Bonus::setCoords(int x, int y)
{
    currentX = x;
    currentY = y;
}

void Bonus::setType(QString type)
{
    this->type = type;
}

QString Bonus::getType()
{
    return type;
}

int Bonus::getValue()
{
    return value;
}

void Bonus::prepareToDelete()
{
    prepareGeometryChange();
}

QString Bonus::serialize()
{
    return QString("%1, %2, %3").arg(type, QString::number(x()), QString::number(y()));
}
