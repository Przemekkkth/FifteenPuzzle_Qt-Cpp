#include "game.h"
#include <QDebug>
QSize Game::RESOLUTION = QSize(256, 256);
const int Game::COUNT_OF_ELEMENTS_GRID = 4;

Game::Game()
    : m_tile_width(64), PATH_TO_TILES(":/images/tiles.png"), PATH_TO_BG(":/images/bg.png"), ITERATION_STEP(1000.0f/60.0f)
{
    //init();
    idealInit();
    //printGrid();
}

void Game::init()
{
    m_numbers.clear();
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

void Game::idealInit()
{
    m_numbers.clear();
    for(int i = 1; i <= 15; ++i)
    {
        m_numbers.push_back(i);
    }
    m_numbers.push_back(0);
    for (int column = 0; column < 4; column++)
    {
        for (int row = 0; row < 4; row++)
        {
            m_grid[row][column] = m_numbers.at( (column * Game::COUNT_OF_ELEMENTS_GRID) + row);
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
