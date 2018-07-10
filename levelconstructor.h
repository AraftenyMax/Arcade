#ifndef LEVELCONSTRUCTOR_H
#define LEVELCONSTRUCTOR_H

#include "map.h"
#include "player.h"
#include "enemy.h"
#include "mesh.h"
#include "lvlconstructorscene.h"
#include <QDialog>
#include <QObject>

namespace Ui {
class LevelConstructor;
}

class LevelConstructor : public QDialog
{
    Q_OBJECT

public:
    explicit LevelConstructor(QWidget *parent = 0);
    void setMap(Map *map);
    ~LevelConstructor();

private slots:
    void on_MeshButton_clicked();

    void on_enemyButton_clicked();

    void on_playerButton_clicked();

    void on_healthBonus_clicked();

    void on_attackBonus_clicked();

    void on_gun1Button_clicked();

    void on_gun2Button_clicked();

    void on_saveButton_clicked();

    void saveMap(QStringList *mapData);

    void loadMap();

    void on_loadMap_clicked();

    void on_deleteButton_clicked();

    void createObject(int x, int y);

    void deleteObject(int x, int y);

signals:
    void mousePressed(int x, int y);

public slots:
    void obtainCoordinates(int x, int y);

private:
    Ui::LevelConstructor *ui;
    QString state = "";
    QString mode = "Create";
    LvlConstructorScene *scene;
    Map *map;
    const int width = 600;
    const int height = 300;
};

#endif // LEVELCONSTRUCTOR_H
