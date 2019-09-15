#include <QDebug>
#include "corner.h"

Corner::Corner(int xx, int yy, int num, bool up, bool down, bool left, bool right): _xGrid(xx), _yGrid(yy), _num(num){
    _direction[UP] = up;
    _direction[DOWN] = down;
    _direction[LEFT] = left;
    _direction[RIGHT] = right;

    for(int i = UP; i <= RIGHT; i++){
        _nextCorner[i] = NAN;
    }

    for(int i = 0; i < 65; i++)
        _distance[i] = INF;
}

int Corner::x(){
    return _x;
}

int Corner::y(){
    return _y;
}

int Corner::xGrid(){
    return _xGrid;
}

int Corner::yGrid(){
    return _yGrid;
}

int Corner::nextDirection(int currentDirection){
    for(int i = UP; i <= RIGHT; i++){
        if(i != currentDirection && _direction[i] == true)
            return i;
    }

    qDebug() << "No other way!" << endl;
    return currentDirection;    // if there is no other way to go, return current direction
}

int Corner::nextCorner(int direction){
    return _nextCorner[direction];
}

/*
void Corner::setNextCorner(Corner *c1, Corner *c2, Corner *c3, Corner *c4){
    for(int i = 0; i <= RIGHT; i++)
        _nextCorner[i] = NAN;

    // left or right
    if(_x == c1->x()){
        if(_y > c1->y()){
            _distance[]
        }
        else
        _distance[] = (_y - corner1->y() > 0) ? _y - corner1->y() : corner1->y() - _y;
    }

    if(corner1 != NAN){
        _nextCorner[UP] = corner1;
    }
    if(corner2 != NAN)
        _nextCorner[DOWN] = corner2;
    if(corner3 != NAN)
        _nextCorner[LEFT] = corner3;
    if(corner4 != NAN)
        _nextCorner[RIGHT] = corner4;
}*/

void Corner::setPos(int xx, int yy){
    _x = xx;
    _y = yy;
}

void Corner::setNextCorner(Corner *c1, Corner *c2, Corner *c3, Corner *c4){
    /* Corner 1 */
    // corner above or below
    if(c1->xGrid() == _xGrid){
        // below
        if(c1->yGrid() > _yGrid){
            _nextCorner[DOWN] = c1->num();
            _distance[c1->num()] = c1->yGrid() - _yGrid;
        }
        // above
        else if(c1->yGrid() < _yGrid){
            _nextCorner[UP] = c1->num();
            _distance[c1->num()] = _yGrid - c1->yGrid();
        }
    }

    // corner on the left or right
    if(c1->yGrid() == _yGrid){
        // on the right
        if(c1->xGrid() > _xGrid){
            _nextCorner[RIGHT] = c1->num();
            _distance[c1->num()] = c1->xGrid() - _xGrid;
        }
        // on the left
        else if(c1->xGrid() < _xGrid){
            _nextCorner[LEFT] = c1->num();
            _distance[c1->num()] = _xGrid - c1->xGrid();
        }
    }

    /* Corner 2 */
    // corner above or below
    if(c2->xGrid() == _xGrid){
        // below
        if(c2->yGrid() > _yGrid){
            _nextCorner[DOWN] = c2->num();
            _distance[c2->num()] = c2->yGrid() - _yGrid;
        }
        // above
        else if(c2->yGrid() < _yGrid){
            _nextCorner[UP] = c2->num();
            _distance[c2->num()] = _yGrid - c2->yGrid();
        }
    }

    // corner on the left or right
    if(c2->yGrid() == _yGrid){
        // on the right
        if(c2->xGrid() > _xGrid){
            _nextCorner[RIGHT] = c2->num();
            _distance[c2->num()] = c2->xGrid() - _xGrid;
        }
        // on the left
        else if(c2->xGrid() < _xGrid){
            _nextCorner[LEFT] = c2->num();
            _distance[c2->num()] = _xGrid - c2->xGrid();
        }
    }

    /* Corner 3 */
    // corner above or below
    if(c3 && c3->xGrid() == _xGrid){
        // below
        if(c3->yGrid() > _yGrid){
            _nextCorner[DOWN] = c3->num();
            _distance[c3->num()] = c3->yGrid() - _yGrid;
        }
        // above
        else if(c3->yGrid() < _yGrid){
            _nextCorner[UP] = c3->num();
            _distance[c3->num()] = _yGrid - c3->yGrid();
        }
    }

    // corner on the left or right
    if(c3 && c3->yGrid() == _yGrid){
        // on the right
        if(c3->xGrid() > _xGrid){
            _nextCorner[RIGHT] = c3->num();
            _distance[c3->num()] = c3->xGrid() - _xGrid;
        }
        // on the left
        else if(c3->xGrid() < _xGrid){
            _nextCorner[LEFT] = c3->num();
            _distance[c3->num()] = _xGrid - c3->xGrid();
        }
    }

    /* Corner 4 */
    // corner above or below
    if(c4 && c4->xGrid() == _xGrid){
        // below
        if(c4->yGrid() > _yGrid){
            _nextCorner[DOWN] = c4->num();
            _distance[c4->num()] = c4->yGrid() - _yGrid;
        }
        // above
        else if(c4->yGrid() < _yGrid){
            _nextCorner[UP] = c4->num();
            _distance[c4->num()] = _yGrid - c4->yGrid();
        }
    }

    // corner on the left or right
    if(c4 && c4->yGrid() == _yGrid){
        // on the right
        if(c4->xGrid() > _xGrid){
            _nextCorner[RIGHT] = c4->num();
            _distance[c4->num()] = c4->xGrid() - _xGrid;
        }
        // on the left
        else if(c4->xGrid() < _xGrid){
            _nextCorner[LEFT] = c4->num();
            _distance[c4->num()] = _xGrid - c4->xGrid();
        }
    }
}

void Corner::setNextCorner(int c1, int d1, int c2, int d2, int c3, int d3, int c4, int d4){
    for(int i = 0; i <= RIGHT; i++)
        _nextCorner[i] = NAN;

    if(c1 != NAN){
        _nextCorner[UP] = c1;
        _distance[c1] = d1;
    }
    if(c2 != NAN){
        _nextCorner[DOWN] = c2;
        _distance[c2] = d2;
    }
    if(c3 != NAN){
        _nextCorner[LEFT] = c3;
        _distance[c3] = d3;
    }
    if(c4 != NAN){
        _nextCorner[RIGHT] = c4;
        _distance[c4] = d4;
    }
}

int Corner::num(){
    return _num;
}
