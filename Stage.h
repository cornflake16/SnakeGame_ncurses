#ifndef __STAGE__
#define __STAGE__
#include <ncurses.h>
#include <iostream>
#include <deque>

//방향키 인덱스 정의
#define UP 8
#define RIGHT 6
#define DOWN 2
#define LEFT 4

//항목별 인덱스 정의
#define EMPTY 0
#define WALL 1
#define IMMUNE_WALL 2
#define SNAKE_HEAD 3
#define SNAKE_BODY 4
#define GROWTH_ITEM 5
#define POISON_ITEM 6
#define GATE 8

using namespace std;

class Stage
{
    int Map[4][21][21];

public:
    Stage();
    void printStage();
    void setMission();
    void isMissionClear();
    void pause();
    void resume();
    void Move(int direction);
    void makeItem();
    void drawMap(int** map);
};

class Gate
{
    void makeGate();
};

class Snake
{
    deque<int> snake;
public:
    void makeSnake();
    void moveSnake();
    void moveGate();
    void eatGrowthItem(){};
    void eatPoisonItem();
};
#endif
