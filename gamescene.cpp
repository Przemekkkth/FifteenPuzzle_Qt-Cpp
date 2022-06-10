#include "gamescene.h"
#include <QDebug>
#include <QTimer>
#include <QGraphicsSceneMouseEvent>

GameScene::GameScene(QObject *parent)
    : QGraphicsScene{parent}, m_game(), m_timer(new QTimer(this)), m_animation(new QPropertyAnimation(this))
{
    loadPixmap();
    setSceneRect(0, 0, m_game.RESOLUTION.width(), m_game.RESOLUTION.height());

    //connect(m_timer, &QTimer::timeout, this, &GameScene::update);
    //m_timer->start(m_game.ITERATION_STEP);

    //update();
    init();
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

void GameScene::init()
{
    clear();
    for (int column = 0; column < 4; column++)
    {
        for (int row = 0; row < 4; row++)
        {
            int n = m_game.m_grid[column][row];
            //qDebug() << "express " << (row * 4) + column ;
            m_pixmapItems[(row * 4) + column] = new PixmapItem(this);
            m_pixmapItems[(row * 4) + column]->setPixmap(m_tilesPixmap[n]);
            m_pixmapItems[(row * 4) + column]->setPos(column * m_game.m_tile_width, row * m_game.m_tile_width);
            addItem(m_pixmapItems[(row * 4) + column]);
        }
    }
}

void GameScene::isPossibleMoveArea()
{
    if(m_clickedX - 1 < 0)
    {
        qDebug() << "X is not valid. Less than 0";
    }
    else if(m_game.m_grid[m_clickedX - 1][m_clickedY] == 0)
    {
        qDebug() << "X is valid";
        m_animation->setTargetObject(m_pixmapItems[m_game.m_grid[m_clickedX][m_clickedY]]);

        m_animation->setPropertyName("posX");
        m_animation->setDuration(2000);
        m_animation->setStartValue(m_pixmapItems[m_game.m_grid[m_clickedX][m_clickedY]]->pos().x());
        m_animation->setEndValue(m_pixmapItems[m_game.m_grid[m_clickedX][m_clickedY]]->pos().x() - m_game.m_tile_width);

        m_animation->start();

    }

    if(m_clickedX + 1 >= Game::COUNT_OF_ELEMENTS_GRID)
    {
        qDebug() << "X is not valid. Greater than 4";
    }
    else if(m_game.m_grid[m_clickedX + 1][m_clickedY] == 0)
    {
        qDebug() << "X is valid";
    }


    if(m_clickedY - 1 < 0)
    {
        qDebug() << "Y is not valid. Less than 0";
    }
    else if(m_game.m_grid[m_clickedX][m_clickedY - 1] == 0)
    {
        qDebug() << "Y is valid";
    }


    if(m_clickedY + 1 >= Game::COUNT_OF_ELEMENTS_GRID)
    {
        qDebug() << "Y is not valid. Greater than 4";
    }
    else if(m_game.m_grid[m_clickedX][m_clickedY + 1] == 0)
    {
        qDebug() << "Y is valid";
    }

}

void GameScene::update()
{
    clear();
    for (int i=0;i<4;i++)
    {
        for (int j=0;j<4;j++)
        {
            int n = m_game.m_grid[i][j];
            QGraphicsPixmapItem *pixmapItem = new QGraphicsPixmapItem(m_tilesPixmap[n]);
            pixmapItem->setPos(i * m_game.m_tile_width, j * m_game.m_tile_width);
            addItem(pixmapItem);
        }
    }
}

void GameScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        QPointF clickedPos =  event->scenePos();
        m_clickedX = static_cast<int>(clickedPos.x()) / m_game.m_tile_width;
        m_clickedY = static_cast<int>(clickedPos.y()) / m_game.m_tile_width;

        //qDebug() << "cPx " << clickedPos.x() << " cPy " << clickedPos.y();
        //qDebug() << "x " << m_clickedX << " y " << m_clickedY;
        qDebug() << m_game.m_grid[m_clickedX][m_clickedY];
        isPossibleMoveArea();
    }

}
