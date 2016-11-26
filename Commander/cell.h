#ifndef CELL_H
#define CELL_H
#include <QMainWindow>

using namespace std;

#define SIZE 10
#define CELLSIZE 60

class Cell
{
    QColor color;
    pair<int, int> position;
public:
    Cell();
    Cell(pair<int, int> pos, bool hasShip)
    {
        position = pos;
        if(hasShip)
        {
            color.setRgb(255,255,255);
        }
        else
            color.setRgb(0,0,0);
    }
    void draw(QMainWindow* w)
    {

    }
};

#endif // CELL_H
