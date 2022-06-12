#include "game.h"
#include <QDebug>
QSize Game::RESOLUTION = QSize(256, 256);
const int Game::COUNT_OF_ELEMENTS_GRID = 4;

Game::Game()
    : m_tile_width(64), PATH_TO_TILES(":/images/tiles.png"), PATH_TO_BG(":/images/bg.png"), ITERATION_STEP(1000.0f/60.0f)
{
    //init();
    idealInit();
    printGrid();
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

bool Game::checkPossibleVictory()
{
    if(m_grid[0][0] == 1 && m_grid[1][0] == 2 && m_grid[2][0] == 3 && m_grid[3][0] == 4
            && m_grid[0][1] == 5 && m_grid[1][1] == 6 && m_grid[2][1] == 7 && m_grid[3][1] == 8
            && m_grid[0][2] == 9 && m_grid[1][2] == 10 && m_grid[2][2] == 11 && m_grid[3][2] == 12
            && m_grid[0][3] == 13 && m_grid[1][3] == 14 && m_grid[2][3] == 15 && m_grid[3][3] == 0
            )
    {
        return true;
    }
    return false;
}
