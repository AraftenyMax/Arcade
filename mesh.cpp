#include "mesh.h"
#include <QString>

Mesh::Mesh(int x, int y)
{
    this->x = x;
    this->y = y;
}

QString Mesh::serialize()
{
    return QString("%1, %2, %3").arg("Mesh", QString::number(x), QString::number(y));
}
