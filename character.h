#ifndef CHARACTER_H
#define CHARACTER_H

#include <QMovie>
#include <QLabel>
#include <QString>
#include "definition.h"
#include "corner.h"

class Character
{
public:
    Character(int xx = 0, int yy = 0, int width = 30, int height = 30);

    virtual QString src() = 0;   // return icon directory
    int x();    // return current x
    int y();    // return current y
    int xGrid();
    int yGrid();
    void setx(int);
    void sety(int);
    void setGrid(int xx, int yy);
    void setOffset(int);
    void setPath(bool path[][31]);
    QMovie* iconGif();
    QLabel* iconLabel();
    void playGif();
    void setIconGif(QMovie*);
    void setIconLabel(QLabel*);
    void start();
    virtual void switchMode(int);
    int direction(); // get current direction
    virtual void setDirection(int);  // give next direction and update current direction
    virtual void move() = 0;
    virtual void stop() = 0;

    virtual void setTarget(Corner*);
    virtual void setTarget(int x, int y);
    void setTarget(Character *p);
    virtual bool reachedTarget();
    virtual void dead();
    void inCorner(bool);
    int getTarget_x();
    int getTarget_y();
    void setCorner(int num);
    int cornerNum();

    void show();
    void hide();

protected:
    bool movable;   // true or false
    bool _mode;  // Chase Mode, Frightened Mode
    int _x, _y;   // x y position of each character
    int _xGrid, _yGrid;
    int _xOrigin, _yOrigin;
    int path[28][31];
    int _offset;
    int _direction;  // UP, DOWN, LEFT, RIGHT
    QMovie *_iconGif;   // play gif of the character
    QLabel *_iconLabel;
    QSize gifSize;
    int _width, _height;
    int speed = 0;
    Character *pacman;
    bool _inCorner;
    int target_x, target_y;
    int _cornerNum;
};

class Pacman: public Character{
public:
    Pacman(int xx = 0, int yy = 0, int width = 30, int height = 30);
    //~Pacman();

    QString src();
    virtual void setDirection(int);
    void eatDot();
    void eatPellet();
    void eatGhost();
    void addPts(int);
    void move();
    void stop();
    void dead();

private:
    int score;
    QString _src[5];    // UP. DOWN. LEFT. RIGHT, DEAD
};

class Ghost: public Character{
public:
    Ghost(int xx = 0, int yy = 0, int width = 30, int height = 30);

    QString src();
    void eaten();
    void revive();
    void switchMode(int);
    virtual void setDirection(int);
    void stop();

    void setTarget(Corner*);
    void setTarget(int x, int y);
    bool reachedTarget();

protected:
    QString _src[3];    // CHASE, FRIGHTENED, REVIVE

};

class Blinky: public Ghost{
public:
    Blinky(int xx = 0, int yy = 0);

    void move();
};

class Pinky: public Ghost{
public:
    Pinky(int xx = 0, int yy = 0);

    void move();
};

class Inky: public Ghost{
public:
    Inky(int xx = 0, int yy = 0);

    void move();
};

class Clyde: public Ghost{
public:
    Clyde(int xx = 0, int yy = 0);

    void move();
};

#endif // CHARACTER_H
