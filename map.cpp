#include "map.h"
#include "enemy.h"
#include "mesh.h"
#include <QList>

Map::Map(int width, int height)
{
    this->width = width;
    this->height = height;
}

void Map::tryPerformAction(QString action, int x, int y)
{

}

void Map::checkNearestMeshes(int x, int y)
{
    foreach(Mesh* m, Meshes)
    {

    }
}

void Map::checkNearestEnemies(int x, int y)
{

}

void Map::checkNearestBonuses(int x, int y)
{

}

void Map::checkNearestWeapons(int x, int y)
{

}

void Map::checkBounds(int x, int y)
{

}
