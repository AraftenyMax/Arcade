#ifndef PLAYERMARKER_H
#define PLAYERMARKER_H
#include <QGraphicsRectItem>
#include <QKeyEvent>


class PlayerMarker: public QGraphicsRectItem
{
public:
    PlayerMarker();
    void keyPressEvent(QKeyEvent *event);
signals:
    void onKeyPressed(QString action, int x, int y);
    ~PlayerMarker();
};

#endif // PLAYERMARKER_H
