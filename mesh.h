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
    static const int width = 10, height = 10;
    static const int markerType = -1;
private:
};

#endif // MESH_H
