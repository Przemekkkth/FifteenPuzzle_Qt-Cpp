#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QGraphicsScene>
#include "game.h"

class QTimer;
class QGraphicsPixmapItem;
class GameScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit GameScene(QObject *parent = nullptr);

signals:

private:
    void loadPixmap();
    Game m_game;
    QPixmap m_mainTilePixmap;
    QPixmap m_tilesPixmap[16];
    QTimer* m_timer;
private slots:
    void update();
};

#endif // GAMESCENE_H
