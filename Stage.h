#ifndef __STAGE__
#define __STAGE__
#include <ncurses.h>
#include <iostream>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include "Something.h"

//방향키 인덱스 정의
#define UP 8
#define DOWN 2
#define RIGHT 6
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
public:
    WINDOW *win;
    WINDOW *game;
    WINDOW *score;
    WINDOW *mission;

    int ***stage;

    Something* Bam;
    Something* gate1;
    Something* gate2;

    Stage();
    ~Stage();
    int getStageNum() const { return STAGE_NUM; }
    int getMapRow() const { return MAP_ROW; }
    int getMapCol() const { return MAP_COL; }
    int getNlines() const { return NLINES; }
    int getNcols() const { return NCOLS; }
    void setMap(int***& stage);
    int** copyMap(int nStage);
    void drawMap(int** map);
    void drawBorders();

    void makeSnake(int **map);

    void setMission();
    void drawMission();
    void pause();
    void resume();

    void EatItem(int item,int dir,int**map);

    void Move(int direction,int** map);
    void appearItem(int**& map);

    void appearGate(int**& map);
    void Gate(Something* head,int** map, int dir);
    void isMissionClear();

    int checkBody(){return Body;}
    bool checkfinish(){return finish;}
    void Gameover();

    int findRoot(Something* gate,int dir,int** map);

private:
    const int STAGE_NUM = 4; //스테이지 개수
    const int MAP_ROW = 25,
              MAP_COL = 50; //맵 세로, 가로 길이
    const int NLINES = 40,
              NCOLS = 110;
    int Body;
    bool finish;
};
#endif
