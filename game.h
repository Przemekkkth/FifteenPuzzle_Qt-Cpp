#ifndef GAME_H
#define GAME_H
#include <QString>
#include <QSize>
#include <QList>

class Game
{
public:
    Game();
    int m_tile_width;
    int m_grid[6][6];
    const QString PATH_TO_TILES;
    static QSize RESOLUTION;
    const float ITERATION_STEP;
    static const int COUNT_OF_ELEMENTS_GRID;

    void init();
    void printGrid();
private:
    QVector<int> m_numbers;
};

#endif // GAME_H
