#ifndef BONUS_H
#define BONUS_H
#include <QString>
#include <QGraphicsRectItem>
#include <QObject>


class Bonus : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    Bonus();
    QString serialize();
    int currentX, currentY;
    void setCoords(int x, int y);
    void setType(QString type);
    void prepareToDelete();
    QString getType();
    int getValue();
    static const int width = 10, height = 10;
    static const int markerHealthBonus = -6, markerAttackBonus = -7;
private:
    int value = 20;
    QString type;
};

#endif // BONUS_H
