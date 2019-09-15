#include <QDebug>
#include "character.h"

Character::Character(int xx, int yy, int width, int height): _x(xx), _y(yy), _xOrigin(xx), _yOrigin(yy), _width(width), _height(height){
    movable = false;
    _mode = CHASE;
    gifSize.setWidth(width);
    gifSize.setHeight(height);
}

int Character::x(){
    return _x;
}

int Character::y(){
    return _y;
}

int Character::xGrid(){
    return _xGrid;
}

int Character::yGrid(){
    return _yGrid;
}

void Character::setx(int xx){
    this->_x = xx;
}

void Character::sety(int yy){
    this->_y = yy;
}

void Character::setGrid(int xx, int yy){
    _xGrid = xx;
    _yGrid = yy;
}

void Character::setPath(bool path[][31]){
    for(int i = 0; i <= 27; i++)
        for(int j = 0; j <= 30; j++)
            this->path[i][j] = path[i][j];
}

QMovie* Character::iconGif(){
    return _iconGif;
}

QLabel* Character::iconLabel(){
    return _iconLabel;
}

void Character::playGif(){
    _iconGif->setScaledSize(gifSize);
    _iconLabel->setMovie(_iconGif);
    _iconLabel->setGeometry(_x-_width/2, _y-_height/2, _width, _height);
    _iconGif->start();
}

void Character::setIconGif(QMovie* iconGif){
    this->_iconGif = iconGif;
}

void Character::setIconLabel(QLabel* iconLabel){
    this->_iconLabel = iconLabel;
}

int Character::direction(){
    return _direction;
}

void Character::setDirection(int new_direction){
    this->_direction = new_direction;
}

void Character::start(){
    speed = 1;
}

void Character::switchMode(int mode){
    _mode = mode;
}

void Character::setTarget(Character *p){
    pacman = p;
}

void Character::setTarget(Corner*){}

void Character::setTarget(int xx, int yy){}

int Character::getTarget_x(){
    return target_x;
}

int Character::getTarget_y(){
    return target_y;
}

bool Character::reachedTarget(){}

void Character::dead(){}

void Character::inCorner(bool inCorner){
    this->_inCorner = inCorner;
}

void Character::setCorner(int cornerNum){
    this->_cornerNum = cornerNum;
}

int Character::cornerNum(){
    return _cornerNum;
}

void Character::show(){
    _iconLabel->show();
}

void Character::hide(){
    _iconLabel->hide();
}

/* Pacman */
Pacman::Pacman(int xx, int yy, int width, int height): Character(xx, yy, width, height), score(0){
    this->_src[UP] = ":/img/src/img/pacman_up.gif";
    this->_src[DOWN] = ":/img/src/img/pacman_down.gif";
    this->_src[LEFT] = ":/img/src/img/pacman_left.gif";
    this->_src[RIGHT] = ":/img/src/img/pacman_right.gif";
    this->_src[DEAD] = ":/img/src/img/pacman_dead.gif";

    _direction = RIGHT;
}

QString Pacman::src(){
    return _src[_direction];    // UP, DOWN, LEFT, RIGHT
}

void Pacman::setDirection(int direction){
    _direction = direction;
    // change gif
    delete _iconGif;    // free previous space
    switch(direction){
    case UP:
        setIconGif(new QMovie(_src[UP]));
        break;
    case DOWN:
        setIconGif(new QMovie(_src[DOWN]));
        break;
    case LEFT:
        setIconGif(new QMovie(_src[LEFT]));
        break;
    case RIGHT:
        setIconGif(new QMovie(_src[RIGHT]));
        break;
    }
    playGif();
}

void Pacman::move(){
    switch(_direction){
    case UP:
        _y -= speed;
        _iconLabel->move(_x-_width/2, _y-_height/2);
        break;
    case DOWN:
        _y += speed;
        _iconLabel->move(_x-_width/2, _y-_height/2);
        break;
    case LEFT:
        _x -= speed;
        _iconLabel->move(_x-_width/2, _y-_height/2);
        break;
    case RIGHT:
        _x += speed;
        _iconLabel->move(_x-_width/2, _y-_height/2);
        break;
    }
}

void Pacman::stop(){
    speed = 0;
}

void Pacman::addPts(int pts){
    score += pts;
}

void Pacman::dead(){
    // change gif
    delete _iconGif;    // free previous space
    setIconGif(new QMovie(_src[DEAD]));
    playGif();
}

/* Ghost */
Ghost::Ghost(int xx, int yy, int width, int height): Character(xx, yy, width, height){
    _src[FRIGHTENED] = ":/img/src/img/ghost_frightened.gif";
    _src[REVIVE] = ":/img/src/img/ghost_revive.gif";
    _direction = RIGHT;
}

QString Ghost::src(){
    return _src[_mode];    // UP, DOWN, LEFT, RIGHT
}

void Ghost::switchMode(int mode){
    delete _iconGif;
    _mode = mode;
    setIconGif(new QMovie(_src[mode]));
    playGif();
}

void Ghost::setDirection(int direction){
    _direction = direction;
}

void Ghost::stop(){
    speed = 0;
}

void Ghost::setTarget(Corner *c){
    target_x = c->x();
    target_y = c->y();
}

void Ghost::setTarget(int xx, int yy){
    target_x = xx;
    target_y = yy;
}

bool Ghost::reachedTarget(){
    if(_x == target_x && _y == target_y){
        return true;
    }
    return false;
}

/* Blinky */
Blinky::Blinky(int xx, int yy): Ghost(xx, yy){
    _src[CHASE] = ":/img/src/img/ghost_red.gif";
}

void Blinky::move(){
    switch(_direction){
    case UP:
        _y -= speed;
        _iconLabel->move(_x-_width/2, _y-_height/2);
        break;
    case DOWN:
        _y += speed;
        _iconLabel->move(_x-_width/2, _y-_height/2);
        break;
    case LEFT:
        _x -= speed;
        _iconLabel->move(_x-_width/2, _y-_height/2);
        break;
    case RIGHT:
        _x += speed;
        _iconLabel->move(_x-_width/2, _y-_height/2);
        break;
    default:
        break;
    }

    setTarget(pacman->x(), pacman->y());

    /*if(_inCorner){
        int xx = _xGrid;
        int yy = _yGrid;
        // on the same vertical line
        if(target_x == _x){
            // pacman is below
            if(target_y > _y){
                if(path[xx][yy+1])
                    setDirection(DOWN);
                else if(path[xx+1][yy])
                    setDirection(RIGHT);
                else if(path[xx][yy-1])
                    setDirection(UP);
                else if(path[xx-1][yy]){
                    setDirection(LEFT);
                }
                else{
                    stop();
                }
            }
            // pacman is above
            else {
                if(path[xx][yy-1])
                    setDirection(UP);
                else if(path[xx+1][yy])
                    setDirection(RIGHT);
                else if(path[xx][yy+1])
                    setDirection(DOWN);
                else if(path[xx-1][yy]){
                    setDirection(LEFT);
                }
                else{
                    stop();
                }
            }
        }
        // pacman is on the right
        else if(target_x > _x){
            // on the same horizontal line
            if(target_y == _y){
                if(path[xx+1][yy])
                    setDirection(RIGHT);
                else if(path[xx][yy+1])
                    setDirection(DOWN);
                else if(path[xx][yy-1])
                    setDirection(UP);
                else if(path[xx-1][yy]){
                    setDirection(LEFT);
                }
                else{
                    stop();
                }
            }
            // pacman is below
            else if(target_y > _y){
                if(pacman->direction() == UP || pacman->direction() == DOWN){
                    if(path[xx+1][yy])
                        setDirection(RIGHT);
                    else if(path[xx][yy+1])
                        setDirection(DOWN);
                    else if(path[xx][yy-1])
                        setDirection(UP);
                    else if(path[xx-1][yy]){
                        setDirection(LEFT);
                    }
                    else{
                        stop();
                    }
                }
                else{
                    if(path[xx][yy+1])
                        setDirection(DOWN);
                    else if(path[xx+1][yy])
                        setDirection(RIGHT);
                    else if(path[xx][yy-1])
                        setDirection(UP);
                    else if(path[xx-1][yy]){
                        setDirection(LEFT);
                    }
                    else{
                        stop();
                    }
                }
            }
            // pacman is above
            else {
                if(pacman->direction() == UP || pacman->direction() == DOWN){
                    if(path[xx+1][yy])
                        setDirection(RIGHT);
                    else if(path[xx][yy-1])
                        setDirection(UP);
                    else if(path[xx][yy+1])
                        setDirection(DOWN);
                    else if(path[xx-1][yy]){
                        setDirection(LEFT);
                    }
                    else{
                        stop();
                    }
                }
                else{
                    if(path[xx][yy-1])
                        setDirection(UP);
                    else if(path[xx+1][yy])
                        setDirection(RIGHT);
                    else if(path[xx][yy+1])
                        setDirection(DOWN);
                    else if(path[xx-1][yy]){
                        setDirection(LEFT);
                    }
                    else{
                        stop();
                    }
                }
            }
        }
        // pacman is on the left
        else {
            if(target_y == _y){
                if(path[xx-1][yy])
                    setDirection(LEFT);
                else if(path[xx][yy+1])
                    setDirection(DOWN);
                else if(path[xx][yy-1])
                    setDirection(UP);
                else if(path[xx+1][yy]){
                    setDirection(RIGHT);
                }
                else {
                    stop();
                }
            }
            // pacman is below
            else if(target_y > _y){
                if(pacman->direction() == UP || pacman->direction() == DOWN){
                    if(path[xx-1][yy])
                        setDirection(LEFT);
                    else if(path[xx][yy+1])
                        setDirection(DOWN);
                    else if(path[xx][yy-1])
                        setDirection(UP);
                    else if(path[xx+1][yy]){
                        setDirection(RIGHT);
                    }
                    else {
                        stop();
                    }

                }
                else{
                    if(path[xx][yy+1])
                        setDirection(DOWN);
                    else if(path[xx-1][yy])
                        setDirection(LEFT);
                    else if(path[xx][yy-1])
                        setDirection(UP);
                    else if(path[xx+1][yy]){
                        setDirection(RIGHT);
                    }
                    else {
                        stop();
                    }
                }
            }
            // pacman is above
            else {
                if(pacman->direction() == UP || pacman->direction() == DOWN){
                    if(path[xx+1][yy])
                        setDirection(LEFT);
                    else if(path[xx][yy-1])
                        setDirection(UP);
                    else if(path[xx][yy+1])
                        setDirection(DOWN);
                    else if(path[xx+1][yy]){
                        setDirection(RIGHT);
                    }
                    else {
                        stop();
                    }
                }
                else{
                    if(path[xx][yy-1])
                        setDirection(UP);
                    else if(path[xx+1][yy])
                        setDirection(LEFT);
                    else if(path[xx][yy+1])
                        setDirection(DOWN);
                    else if(path[xx+1][yy]){
                        setDirection(RIGHT);
                    }
                    else {
                        stop();
                    }
                }
            }
        }
    }*/
}


/* Pinky */
Pinky::Pinky(int xx, int yy): Ghost(xx, yy){
    _src[CHASE] = ":/img/src/img/ghost_pink.gif";
}

void Pinky::move(){
    switch(_direction){
    case UP:
        _y -= speed;
        _iconLabel->move(_x-_width/2, _y-_height/2);
        break;
    case DOWN:
        _y += speed;
        _iconLabel->move(_x-_width/2, _y-_height/2);
        break;
    case LEFT:
        _x -= speed;
        _iconLabel->move(_x-_width/2, _y-_height/2);
        break;
    case RIGHT:
        _x += speed;
        _iconLabel->move(_x-_width/2, _y-_height/2);
        break;
    default:
        break;
    }

    switch(pacman->direction()){
    case UP:
        target_x = pacman->x();
        target_y = pacman->y()-100;
        break;
    case DOWN:
        target_x = pacman->x();
        target_y = pacman->y()+100;
        break;
    case LEFT:
        target_x = pacman->x()-100;
        target_y = pacman->y();
        break;
    case RIGHT:
        target_x = pacman->x()+100;
        target_y = pacman->y();
        break;
    }

    /*if(_inCorner){
        int xx = _xGrid;
        int yy = _yGrid;
        // on the same vertical line
        if(target_x == _x){
            // pacman is below
            if(target_y > _y){
                if(path[xx][yy+1])
                    setDirection(DOWN);
                else if(path[xx+1][yy])
                    setDirection(RIGHT);
                else if(path[xx][yy-1])
                    setDirection(UP);
                else if(path[xx-1][yy]){
                    setDirection(LEFT);
                }
                else{
                    stop();
                }
            }
            // pacman is above
            else {
                if(path[xx][yy-1])
                    setDirection(UP);
                else if(path[xx+1][yy])
                    setDirection(RIGHT);
                else if(path[xx][yy+1])
                    setDirection(DOWN);
                else if(path[xx-1][yy]){
                    setDirection(LEFT);
                }
                else{
                    stop();
                }
            }
        }
        // pacman is on the right
        else if(target_x > _x){
            // on the same horizontal line
            if(target_y == _y){
                if(path[xx+1][yy])
                    setDirection(RIGHT);
                else if(path[xx][yy+1])
                    setDirection(DOWN);
                else if(path[xx][yy-1])
                    setDirection(UP);
                else if(path[xx-1][yy]){
                    setDirection(LEFT);
                }
                else{
                    stop();
                }
            }
            // pacman is below
            else if(target_y > _y){
                if(pacman->direction() == UP || pacman->direction() == DOWN){
                    if(path[xx+1][yy])
                        setDirection(RIGHT);
                    else if(path[xx][yy+1])
                        setDirection(DOWN);
                    else if(path[xx][yy-1])
                        setDirection(UP);
                    else if(path[xx-1][yy]){
                        setDirection(LEFT);
                    }
                    else{
                        stop();
                    }
                }
                else{
                    if(path[xx][yy+1])
                        setDirection(DOWN);
                    else if(path[xx+1][yy])
                        setDirection(RIGHT);
                    else if(path[xx][yy-1])
                        setDirection(UP);
                    else if(path[xx-1][yy]){
                        setDirection(LEFT);
                    }
                    else{
                        stop();
                    }
                }
            }
            // pacman is above
            else {
                if(pacman->direction() == UP || pacman->direction() == DOWN){
                    if(path[xx+1][yy])
                        setDirection(RIGHT);
                    else if(path[xx][yy-1])
                        setDirection(UP);
                    else if(path[xx][yy+1])
                        setDirection(DOWN);
                    else if(path[xx-1][yy]){
                        setDirection(LEFT);
                    }
                    else{
                        stop();
                    }
                }
                else{
                    if(path[xx][yy-1])
                        setDirection(UP);
                    else if(path[xx+1][yy])
                        setDirection(RIGHT);
                    else if(path[xx][yy+1])
                        setDirection(DOWN);
                    else if(path[xx-1][yy]){
                        setDirection(LEFT);
                    }
                    else{
                        stop();
                    }
                }
            }
        }
        // pacman is on the left
        else {
            if(target_y == _y){
                if(path[xx-1][yy])
                    setDirection(LEFT);
                else if(path[xx][yy+1])
                    setDirection(DOWN);
                else if(path[xx][yy-1])
                    setDirection(UP);
                else if(path[xx+1][yy]){
                    setDirection(RIGHT);
                }
                else {
                    stop();
                }
            }
            // pacman is below
            else if(target_y > _y){
                if(pacman->direction() == UP || pacman->direction() == DOWN){
                    if(path[xx-1][yy])
                        setDirection(LEFT);
                    else if(path[xx][yy+1])
                        setDirection(DOWN);
                    else if(path[xx][yy-1])
                        setDirection(UP);
                    else if(path[xx+1][yy]){
                        setDirection(RIGHT);
                    }
                    else {
                        stop();
                    }

                }
                else{
                    if(path[xx][yy+1])
                        setDirection(DOWN);
                    else if(path[xx-1][yy])
                        setDirection(LEFT);
                    else if(path[xx][yy-1])
                        setDirection(UP);
                    else if(path[xx+1][yy]){
                        setDirection(RIGHT);
                    }
                    else {
                        stop();
                    }
                }
            }
            // pacman is above
            else {
                if(pacman->direction() == UP || pacman->direction() == DOWN){
                    if(path[xx+1][yy])
                        setDirection(LEFT);
                    else if(path[xx][yy-1])
                        setDirection(UP);
                    else if(path[xx][yy+1])
                        setDirection(DOWN);
                    else if(path[xx+1][yy]){
                        setDirection(RIGHT);
                    }
                    else {
                        stop();
                    }
                }
                else{
                    if(path[xx][yy-1])
                        setDirection(UP);
                    else if(path[xx+1][yy])
                        setDirection(LEFT);
                    else if(path[xx][yy+1])
                        setDirection(DOWN);
                    else if(path[xx+1][yy]){
                        setDirection(RIGHT);
                    }
                    else {
                        stop();
                    }
                }
            }
        }
    }*/
}


/* Inky */
Inky::Inky(int xx, int yy): Ghost(xx, yy){
    _src[CHASE] = ":/img/src/img/ghost_cyan.gif";
}

void Inky::move(){
    switch(_direction){
    case UP:
        _y -= speed;
        _iconLabel->move(_x-_width/2, _y-_height/2);
        break;
    case DOWN:
        _y += speed;
        _iconLabel->move(_x-_width/2, _y-_height/2);
        break;
    case LEFT:
        _x -= speed;
        _iconLabel->move(_x-_width/2, _y-_height/2);
        break;
    case RIGHT:
        _x += speed;
        _iconLabel->move(_x-_width/2, _y-_height/2);
        break;
    default:
        break;
    }
}


/*Clyde */
Clyde::Clyde(int xx, int yy): Ghost(xx, yy){
    _src[CHASE] = ":/img/src/img/ghost_orange.gif";
}

void Clyde::move(){
    switch(_direction){
    case UP:
        _y -= speed;
        _iconLabel->move(_x-_width/2, _y-_height/2);
        break;
    case DOWN:
        _y += speed;
        _iconLabel->move(_x-_width/2, _y-_height/2);
        break;
    case LEFT:
        _x -= speed;
        _iconLabel->move(_x-_width/2, _y-_height/2);
        break;
    case RIGHT:
        _x += speed;
        _iconLabel->move(_x-_width/2, _y-_height/2);
        break;
    default:
        break;
    }
}
