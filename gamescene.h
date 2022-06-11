#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QPropertyAnimation>
#include "pixmapitem.h"
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
    void move();
    void updatePixmaps();

    Game m_game;
    QPixmap m_mainTilePixmap;
    QPixmap m_tilesPixmap[16];
    QTimer *m_timer;
    PixmapItem *m_pixmapItems[4][4];
    QPropertyAnimation *m_moveAnimation;

    int m_clickedX, m_clickedY, m_clickedNumber;
    bool m_isAnimationContinues;
private slots:    

    void finishMoveAnim();
    // QGraphicsScene interface
protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void keyPressEvent(QKeyEvent *event) override;
};

#endif // GAMESCENE_H
