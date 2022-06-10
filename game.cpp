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
    int number = 0;
    for (int column = 0; column <4; column++)
    {
        for (int row = 0; row < 4; row++)
        {
            m_grid[column][row] = number;
            number++;
        }
    }
}

void Game::printGrid()
{
    for(int column = 0; column < 4; ++column)
    {
        for(int row = 0; row < 4; ++row)
        {
            int number = m_grid[column][row];
            qDebug() << "[" << column << "] [" << row << "] = " << number;
        }
    }
}
