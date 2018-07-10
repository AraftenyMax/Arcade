#include "mesh.h"
#include <QString>

Mesh::Mesh()
{
}

QString Mesh::serialize()
{
    return QString("%1, %2, %3").arg("Mesh", QString::number(x()), QString::number(y()));
}
