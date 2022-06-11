#include "game.h"
#include <QDebug>
QSize Game::RESOLUTION = QSize(256, 256);
const int Game::COUNT_OF_ELEMENTS_GRID = 4;

Game::Game()
    : m_tile_width(64), PATH_TO_TILES(":/images/tiles.png"), ITERATION_STEP(1000.0f/60.0f)
{
    init();
    printGrid();
}

void Game::init()
{
    for(int i = 0; i < 16; ++i)
    {
        m_numbers.push_back(i);
    }
    srand(time(0));
    for (int column = 0; column < 4; column++)
    {
        for (int row = 0; row < 4; row++)
        {
            int index = rand()%m_numbers.size();
            m_grid[column][row] = m_numbers.at(index);
            m_numbers.removeAt(index);
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
