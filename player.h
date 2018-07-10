#ifndef PLAYER_H
#define PLAYER_H
#include <QGraphicsRectItem>
#include <QObject>
#include <QKeyEvent>

class Player : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    Player();
    QString serialize();
    void keyPressEvent(QKeyEvent *event);
    static const int width = 10, height = 10;
    static const int markerType = 0;
signals:
    void onKeyPressed(QString action, int x, int y);
private:
    int healthPoints = 100;
    int visibleRange = 50;
    QString name;
};

#endif // PLAYER_H
