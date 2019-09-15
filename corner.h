#ifndef CORNER_H
#define CORNER_H

#include "definition.h"

class Corner
{
public:
    Corner(int xx = 0, int yy = 0, int num = NAN, bool up = false, bool down = false, bool left = false, bool right = false);

    int x();
    int y();
    int xGrid();
    int yGrid();
    int num();
    int nextDirection(int); // give current direction, then return next direction when ghosts meet corners
    int nextCorner(int);
    void setPos(int xx, int yy);
    void setNextCorner(Corner*, Corner*, Corner* = nullptr, Corner* = nullptr);   // corner1(UP), corner2(DOWN), corner3(LEFT), corner4(RIGHT)
    void setNextCorner(int c1, int d1, int c2, int d2, int c3 = NAN, int d3 = NAN, int c4 = NAN, int d4 = NAN);   // corner1(UP), corner2(DOWN), corner3(LEFT), corner4(RIGHT)

private:
    int _x, _y;
    int _xGrid, _yGrid;   // x: 0~27, y: 0~30
    int _num;
    bool _direction[4];  // UP, DOWN, LEFT, RIGHT
                        // will be true if the direction is available
    int _nextCorner[4]; // corners connected with this corner
    int _distance[65];  // distance between this corner and connected corner
                        // not connected: INF(1e9)
};

#endif // CORNER_H
