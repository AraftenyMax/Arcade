#ifndef MESH_H
#define MESH_H
#include <QString>
#include <QGraphicsRectItem>
#include <QObject>

class Mesh : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    Mesh();
    QString serialize();
    void setCoords(int x, int y);
    static const int width = 10, height = 10;
    static const int markerType = -1;
    int currentX, currentY;
private:
};

#endif // MESH_H
