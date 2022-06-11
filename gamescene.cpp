#include "gamescene.h"
#include <QDebug>
#include <QTimer>
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>

GameScene::GameScene(QObject *parent)
    : QGraphicsScene{parent}, m_game(), m_timer(new QTimer(this)), m_leftAnimation(new QPropertyAnimation(this)),
      m_rightAnimation(new QPropertyAnimation(this)), m_upAnimation(new QPropertyAnimation(this)),
      m_downAnimation(new QPropertyAnimation(this)),
      m_stopClicking(false)
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
            m_pixmapItems[column][row] = new PixmapItem(this);
            m_pixmapItems[column][row]->setPixmap(m_tilesPixmap[n]);
            m_pixmapItems[column][row]->setPos(column * m_game.m_tile_width, row * m_game.m_tile_width);
            addItem(m_pixmapItems[column][row]);
        }
    }
}

void GameScene::isPossibleMoveArea()
{
    int duration = 1500;
    QEasingCurve::Type easingCurveType = QEasingCurve::InOutBounce;

    if(m_clickedX - 1 < 0)
    {
        qDebug() << "X - 1 is not valid. Less than 0";
    }
    else if(m_game.m_grid[m_clickedX - 1][m_clickedY] == 0)
    {
        qDebug() << "X - 1 is valid";

        m_stopClicking = true;

        m_leftAnimation->setTargetObject(m_pixmapItems[m_clickedX][m_clickedY]);
        m_leftAnimation->setPropertyName("posX");
        m_leftAnimation->setDuration(duration);
        m_leftAnimation->setEasingCurve(easingCurveType);
        m_leftAnimation->setStartValue(m_pixmapItems[m_clickedX][m_clickedY]->pos().x());
        m_leftAnimation->setEndValue(m_pixmapItems[m_clickedX][m_clickedY]->pos().x() - m_game.m_tile_width);
        m_leftAnimation->start();

        //replace in grid
        m_game.m_grid[m_clickedX - 1][m_clickedY] = m_game.m_grid[m_clickedX][m_clickedY];
        m_game.m_grid[m_clickedX][m_clickedY] = 0;
        //////////////////////////////////////////
        connect(m_leftAnimation, &QPropertyAnimation::finished, this, &GameScene::finishLeftAnim, Qt::UniqueConnection);
    }

    if(m_clickedX + 1 >= Game::COUNT_OF_ELEMENTS_GRID)
    {
        qDebug() << "X + 1 is not valid. Greater than 4";
    }
    else if(m_game.m_grid[m_clickedX + 1][m_clickedY] == 0)
    {
        qDebug() << "X + 1 is valid";

        m_stopClicking = true;

        m_rightAnimation->setTargetObject(m_pixmapItems[m_clickedX][m_clickedY]);
        m_rightAnimation->setPropertyName("posX");
        m_rightAnimation->setDuration(duration);
        m_rightAnimation->setEasingCurve(easingCurveType);
        m_rightAnimation->setStartValue(m_pixmapItems[m_clickedX][m_clickedY]->pos().x());
        m_rightAnimation->setEndValue(m_pixmapItems[m_clickedX][m_clickedY]->pos().x() + m_game.m_tile_width);
        m_rightAnimation->start();

        //replace in grid
        m_game.m_grid[m_clickedX + 1][m_clickedY] = m_game.m_grid[m_clickedX][m_clickedY];
        m_game.m_grid[m_clickedX][m_clickedY] = 0;

        ///////////////////////////////////////////
        connect(m_rightAnimation, &QPropertyAnimation::finished, this, &GameScene::finishRightAnim, Qt::UniqueConnection);
    }


    if(m_clickedY - 1 < 0)
    {
        qDebug() << "Y is not valid. Less than 0";
    }
    else if(m_game.m_grid[m_clickedX][m_clickedY - 1] == 0)
    {
        qDebug() << "Y is valid";

        m_upAnimation->setTargetObject(m_pixmapItems[m_clickedX][m_clickedY]);
        m_upAnimation->setPropertyName("posY");
        m_upAnimation->setDuration(duration);
        m_upAnimation->setEasingCurve(easingCurveType);
        m_upAnimation->setStartValue(m_pixmapItems[m_clickedX][m_clickedY]->pos().y());
        m_upAnimation->setEndValue(m_pixmapItems[m_clickedX][m_clickedY]->pos().y() - m_game.m_tile_width);
        m_upAnimation->start();

        //replace in grid
        m_game.m_grid[m_clickedX][m_clickedY - 1] = m_game.m_grid[m_clickedX][m_clickedY];
        m_game.m_grid[m_clickedX][m_clickedY] = 0;

        connect(m_upAnimation, &QPropertyAnimation::finished, this, &GameScene::finishUpAnim, Qt::UniqueConnection);
    }


    if(m_clickedY + 1 >= Game::COUNT_OF_ELEMENTS_GRID)
    {
        qDebug() << "Y is not valid. Greater than 4";
    }
    else if(m_game.m_grid[m_clickedX][m_clickedY + 1] == 0)
    {
        qDebug() << "Y is valid";

        m_downAnimation->setTargetObject(m_pixmapItems[m_clickedX][m_clickedY]);
        m_downAnimation->setPropertyName("posY");
        m_downAnimation->setDuration(duration);
        m_downAnimation->setEasingCurve(easingCurveType);
        m_downAnimation->setStartValue(m_pixmapItems[m_clickedX][m_clickedY]->pos().y());
        m_downAnimation->setEndValue(m_pixmapItems[m_clickedX][m_clickedY]->pos().y() + m_game.m_tile_width);
        m_downAnimation->start();

        //replace in grid
        m_game.m_grid[m_clickedX][m_clickedY + 1] = m_game.m_grid[m_clickedX][m_clickedY];
        m_game.m_grid[m_clickedX][m_clickedY] = 0;

        connect(m_downAnimation, &QPropertyAnimation::finished, this, &GameScene::finishDownAnim);
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

void GameScene::finishLeftAnim()
{
    //m_pixmapItems[m_clickedX][m_clickedY]->setPosX(m_pixmapItems[m_clickedX][m_clickedY]->pos().x() + m_game.m_tile_width);
    updatePixmaps();
    m_stopClicking = false;
}

void GameScene::finishRightAnim()
{
    //m_pixmapItems[m_clickedX][m_clickedY]->setPosX(m_pixmapItems[m_clickedX][m_clickedY]->pos().x() - m_game.m_tile_width);
    updatePixmaps();
    m_stopClicking = false;
}

void GameScene::finishUpAnim()
{
    //m_pixmapItems[m_clickedX][m_clickedY]->setPosY(m_pixmapItems[m_clickedX][m_clickedY]->pos().y() + m_game.m_tile_width);
    updatePixmaps();
    m_stopClicking = false;
}

void GameScene::finishDownAnim()
{
    //m_pixmapItems[m_clickedX][m_clickedY]->setPosY(m_pixmapItems[m_clickedX][m_clickedY]->pos().y() - m_game.m_tile_width);
    updatePixmaps();
    m_stopClicking = false;
}

void GameScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::LeftButton && !m_stopClicking)
    {
        QPointF clickedPos =  event->scenePos();
        m_clickedX = static_cast<int>(clickedPos.x()) / m_game.m_tile_width;
        m_clickedY = static_cast<int>(clickedPos.y()) / m_game.m_tile_width;

        //qDebug() << "cPx " << clickedPos.x() << " cPy " << clickedPos.y();
        //qDebug() << "x " << m_clickedX << " y " << m_clickedY;
        qDebug() << m_game.m_grid[m_clickedX][m_clickedY];
        m_clickedNumber = m_game.m_grid[m_clickedX][m_clickedY];
        isPossibleMoveArea();
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
