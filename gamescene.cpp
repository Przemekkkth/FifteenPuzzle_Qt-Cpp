#include "gamescene.h"
#include <QDebug>
#include <QTimer>
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>

GameScene::GameScene(QObject *parent)
    : QGraphicsScene{parent}, m_game(), m_timer(new QTimer(this)), m_moveAnimation(new QPropertyAnimation(this)),
      m_isAnimationContinues(false)
{
    loadPixmap();
    setSceneRect(0, 0, m_game.RESOLUTION.width(), m_game.RESOLUTION.height());
    init();
    connect(m_moveAnimation, &QPropertyAnimation::finished, this, &GameScene::finishMoveAnim);
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

    if(m_bgPixmap.load(m_game.PATH_TO_BG))
    {
        qDebug() << "BgPixmap is loaded successfully";
    }
    else
    {
        qDebug() << "BgPixmap is not loaded successfully";
    }
}

void GameScene::init()
{
    clear();
    QGraphicsPixmapItem *bgItem = new QGraphicsPixmapItem(m_bgPixmap);
    bgItem->setZValue(-1);
    addItem(bgItem);
    for (int column = 0; column < 4; column++)
    {
        for (int row = 0; row < 4; row++)
        {
            int n = m_game.m_grid[column][row];
            //qDebug() << "express " << (row * 4) + column ;
            m_pixmapItems[column][row] = new PixmapItem(this);
            m_pixmapItems[column][row]->setPixmap(m_tilesPixmap[n]);
            m_pixmapItems[column][row]->setPos(column * m_game.m_tile_width, row * m_game.m_tile_width);
            addItem(m_pixmapItems[column][row]);
        }
    }
}

void GameScene::move()
{
    int duration = 1500;
    QEasingCurve::Type easingCurveType = QEasingCurve::InOutBounce;

    bool isAnimation = false;
    if(m_clickedX - 1 < 0)
    {
        qDebug() << "X - 1 is not valid. Less than 0";

   }
    else if(m_game.m_grid[m_clickedX - 1][m_clickedY] == 0)
    {
        qDebug() << "X - 1 is valid";
        isAnimation = true;
        m_moveAnimation->setTargetObject(m_pixmapItems[m_clickedX][m_clickedY]);
        m_moveAnimation->setPropertyName("posX");
        m_moveAnimation->setDuration(duration);
        m_moveAnimation->setEasingCurve(easingCurveType);
        m_moveAnimation->setStartValue(m_pixmapItems[m_clickedX][m_clickedY]->pos().x());
        m_moveAnimation->setEndValue(m_pixmapItems[m_clickedX][m_clickedY]->pos().x() - m_game.m_tile_width);
        m_moveAnimation->start();

        //replace in grid
        m_game.m_grid[m_clickedX - 1][m_clickedY] = m_game.m_grid[m_clickedX][m_clickedY];
        m_game.m_grid[m_clickedX][m_clickedY] = 0;
    }

    if(m_clickedX + 1 >= Game::COUNT_OF_ELEMENTS_GRID)
    {
        qDebug() << "X + 1 is not valid. Greater than 4";
    }
    else if(m_game.m_grid[m_clickedX + 1][m_clickedY] == 0)
    {
        qDebug() << "X + 1 is valid";

        isAnimation = true;

        m_moveAnimation->setTargetObject(m_pixmapItems[m_clickedX][m_clickedY]);
        m_moveAnimation->setPropertyName("posX");
        m_moveAnimation->setDuration(duration);
        m_moveAnimation->setEasingCurve(easingCurveType);
        m_moveAnimation->setStartValue(m_pixmapItems[m_clickedX][m_clickedY]->pos().x());
        m_moveAnimation->setEndValue(m_pixmapItems[m_clickedX][m_clickedY]->pos().x() + m_game.m_tile_width);
        m_moveAnimation->start();

        //replace in grid
        m_game.m_grid[m_clickedX + 1][m_clickedY] = m_game.m_grid[m_clickedX][m_clickedY];
        m_game.m_grid[m_clickedX][m_clickedY] = 0;

    }


    if(m_clickedY - 1 < 0)
    {
        qDebug() << "Y is not valid. Less than 0";
    }
    else if(m_game.m_grid[m_clickedX][m_clickedY - 1] == 0)
    {
        qDebug() << "Y is valid";
        isAnimation = true;
        m_moveAnimation->setTargetObject(m_pixmapItems[m_clickedX][m_clickedY]);
        m_moveAnimation->setPropertyName("posY");
        m_moveAnimation->setDuration(duration);
        m_moveAnimation->setEasingCurve(easingCurveType);
        m_moveAnimation->setStartValue(m_pixmapItems[m_clickedX][m_clickedY]->pos().y());
        m_moveAnimation->setEndValue(m_pixmapItems[m_clickedX][m_clickedY]->pos().y() - m_game.m_tile_width);
        m_moveAnimation->start();

        //replace in grid
        m_game.m_grid[m_clickedX][m_clickedY - 1] = m_game.m_grid[m_clickedX][m_clickedY];
        m_game.m_grid[m_clickedX][m_clickedY] = 0;
    }


    if(m_clickedY + 1 >= Game::COUNT_OF_ELEMENTS_GRID)
    {
        qDebug() << "Y is not valid. Greater than 4";
    }
    else if(m_game.m_grid[m_clickedX][m_clickedY + 1] == 0)
    {
        qDebug() << "Y is valid";
        isAnimation = true;
        m_moveAnimation->setTargetObject(m_pixmapItems[m_clickedX][m_clickedY]);
        m_moveAnimation->setPropertyName("posY");
        m_moveAnimation->setDuration(duration);
        m_moveAnimation->setEasingCurve(easingCurveType);
        m_moveAnimation->setStartValue(m_pixmapItems[m_clickedX][m_clickedY]->pos().y());
        m_moveAnimation->setEndValue(m_pixmapItems[m_clickedX][m_clickedY]->pos().y() + m_game.m_tile_width);
        m_moveAnimation->start();

        //replace in grid
        m_game.m_grid[m_clickedX][m_clickedY + 1] = m_game.m_grid[m_clickedX][m_clickedY];
        m_game.m_grid[m_clickedX][m_clickedY] = 0;
    }

    if(!isAnimation)
    {
        m_isAnimationContinues = false;
    }
}

void GameScene::updatePixmaps()
{
    for (int column = 0; column < Game::COUNT_OF_ELEMENTS_GRID ; column++)
    {
        for (int row = 0; row < Game::COUNT_OF_ELEMENTS_GRID; row++)
        {
            int n = m_game.m_grid[column][row];
            m_pixmapItems[column][row]->setPixmap(m_tilesPixmap[n]);
            m_pixmapItems[column][row]->setPos(column * m_game.m_tile_width, row * m_game.m_tile_width);
        }
    }
}

void GameScene::finishMoveAnim()
{
    updatePixmaps();
    m_isAnimationContinues = false;
}

void GameScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::LeftButton && !m_isAnimationContinues)
    {
        m_isAnimationContinues = true;
        QPointF clickedPos =  event->scenePos();
        m_clickedX = static_cast<int>(clickedPos.x()) / m_game.m_tile_width;
        m_clickedY = static_cast<int>(clickedPos.y()) / m_game.m_tile_width;
        m_clickedNumber = m_game.m_grid[m_clickedX][m_clickedY];
        move();
        if( m_game.checkPossibleVictory() )
        {
            qDebug() << "VICTORY";
        }
        else
        {
            qDebug() << "NOT VICTORY";
        }
    }

}

void GameScene::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_P:
    {
        qDebug() << "Printed ";
        m_game.printGrid();
    }
        break;
    }
    QGraphicsScene::keyPressEvent(event);
}
