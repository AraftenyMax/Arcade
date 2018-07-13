#ifndef PLAYWINDOW_H
#define PLAYWINDOW_H

#include <QDialog>
#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <map.h>
#include <QList>
#include <QCloseEvent>

namespace Ui {
class PlayWindow;
}

class PlayWindow : public QDialog
{
    Q_OBJECT

public:
    explicit PlayWindow(QWidget *parent = 0);
    void createGameObject(int x, int y, QString type);
    void startGame(QString mapName);
    void loadMap(QString path);
    void drawMap();
    void closeEvent(QCloseEvent *event);
    ~PlayWindow();

signals:
    void finishGame();
    void onHpChanged(int HP);
public slots:
    void CloseWindow();
    void changeHp(int HP);

private:
    Ui::PlayWindow *ui;
    QGraphicsScene *scene;
    int width = 600;
    int height = 300;
    QString testMap = "G:/Development/build-Game-Desktop_Qt_5_10_1_MinGW_32bit-Debug/level1.csv";
    QList<QGraphicsRectItem*> markers;
    Map *map;
};

#endif // PLAYWINDOW_H
