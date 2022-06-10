#include "game.h"
#include <QDebug>
QSize Game::RESOLUTION = QSize(256, 256);

Game::Game()
    : m_tile_width(64), PATH_TO_TILES(":/images/tiles.png"), ITERATION_STEP(1000.0f/60.0f)
{
    init();
    printGrid();
}

void Game::init()
{
    int n=0;
    for (int i=0;i<4;i++)
    {
        for (int j=0;j<4;j++)
        {
            n++;
            m_grid[i][j] = n;
        }
    }
    int stop = 0;
}

void Game::printGrid()
{
    for(int i = 0; i < 4; ++i)
    {
        for(int j = 0; j < 4; ++j)
        {
            int n = m_grid[i][j];
            qDebug() << "[" << i << "] [" << j << "] = " << n;
        }
    }
}
