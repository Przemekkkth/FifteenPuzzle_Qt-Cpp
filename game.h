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
    const QString PATH_TO_BG;
    const QString PATH_TO_VICTORY_BG;
    static QSize RESOLUTION;
    const float ITERATION_STEP;
    static const int COUNT_OF_ELEMENTS_GRID;
    bool m_isVictoryState;

    void init();
    void idealInit();
    void initWin();
    void printGrid();
    bool checkPossibleVictory();
private:
    QVector<int> m_numbers;
};

#endif // GAME_H
