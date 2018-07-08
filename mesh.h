#ifndef MESH_H
#define MESH_H
#include <QString>

class Mesh
{
public:
    Mesh(int x, int y);
    QString serialize();
    static const int width = 10, height = 10;
private:
    int x;
    int y;
};

#endif // MESH_H
