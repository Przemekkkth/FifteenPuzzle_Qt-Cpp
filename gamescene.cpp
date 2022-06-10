#include "gamescene.h"
#include <QDebug>
#include <QTimer>
#include <QGraphicsPixmapItem>

GameScene::GameScene(QObject *parent)
    : QGraphicsScene{parent}, m_game(), m_timer(new QTimer(this))
{
    loadPixmap();
    setSceneRect(0, 0, m_game.RESOLUTION.width(), m_game.RESOLUTION.height());

    connect(m_timer, &QTimer::timeout, this, &GameScene::update);
    m_timer->start(m_game.ITERATION_STEP);
}

void GameScene::loadPixmap()
{
    if(m_mainTilePixmap.load(m_game.PATH_TO_TILES))
    {
        qDebug() << "MainTilePixmap is loaded successfully";
    }
    else
    {
        qDebug() << "MainTilePixmap is not loaded successfully";
    }
    for(int i = 0; i < 16; ++i)
    {
        m_tilesPixmap[i] = m_mainTilePixmap.copy(i*m_game.m_tile_width, 0, m_game.m_tile_width, m_game.m_tile_width);
    }
}

void GameScene::update()
{
    clear();
    for (int i=0;i<4;i++)
    {
        for (int j=0;j<4;j++)
        {
            int n = m_game.m_grid[i][j] - 1;
            QGraphicsPixmapItem *pixmapItem = new QGraphicsPixmapItem(m_tilesPixmap[n]);
            pixmapItem->setPos(j*m_game.m_tile_width, i*m_game.m_tile_width);
            addItem(pixmapItem);
        }
    }
}
