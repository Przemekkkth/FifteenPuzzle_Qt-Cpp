#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QPropertyAnimation>
#include "game.h"

class QTimer;

class GameScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit GameScene(QObject *parent = nullptr);

signals:

private:
    void loadPixmap();
    void init();
    void isPossibleMoveArea();
    Game m_game;
    QPixmap m_mainTilePixmap;
    QPixmap m_tilesPixmap[16];
    QTimer* m_timer;
    QGraphicsPixmapItem m_pixmapItems[16];
    QPropertyAnimation m_animation;

    int m_clickedX, m_clickedY;
private slots:
    void update();

    // QGraphicsScene interface
protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif // GAMESCENE_H
