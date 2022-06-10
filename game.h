#ifndef GAME_H
#define GAME_H
#include <QString>
#include <QSize>

class Game
{
public:
    Game();
    int m_tile_width;
    int m_grid[6][6];
    const QString PATH_TO_TILES;
    static QSize RESOLUTION;
    const float ITERATION_STEP;

    void init();
    void printGrid();
};

#endif // GAME_H
