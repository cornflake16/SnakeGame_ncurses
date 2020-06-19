#ifndef __STAGE__
#define __STAGE__
#include <ncurses.h>
#include <iostream>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <random>
#include <unistd.h>
#include <vector>
#include "Something.h"

//방향키 인덱스 정의
#define UP KEY_UP
#define DOWN KEY_DOWN
#define RIGHT KEY_RIGHT
#define LEFT KEY_LEFT
#define ESC 27
#define PAUSE 112

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
    int ***stage;
    int **map;
    int dir;
    bool chkEnter;

    vector<pair<int, int>> itemPos, gatePos;

    // window variables
    WINDOW *game;
    WINDOW *score;
    WINDOW *mission;

    // mission variables
    int stat[4];
    int statMission[4];

    // mission check variables
    char chkMission[4];

    Something *Bam;
    Something *gate1;
    Something *gate2;

    Stage();
    ~Stage();
    int getStageNum() const { return STAGE_NUM; }
    int getNlines() const { return NLINES; }
    int getNcols() const { return NCOLS; }
    int getMapRow() const { return MAP_ROW; }
    int getMapCol() const { return MAP_COL; }
    void setMap();
    void copyMap(int nStage);
    void drawMap();
    void levelUp() {level++;}

    void makeSnake();
    void moveSnake();
    void eatItem(int item);
    int findRoot(Something *gate);

    void appearItem();
    void appearGate();
    void disappearItem();
    void disappearGate();
    void enterGate(Something *head);

    void setMission();
    bool isMissionClear();

    bool checkGameOver() { return finish; }
    void Gameover();
    void alert(int color, int bkgdColor, const string msg);

private:
    const int STAGE_NUM = 4; //스테이지 개수
    const int NLINES = 40,
              NCOLS = 110;
    const int MAP_ROW = 25,
              MAP_COL = 50;
    const int ROW_END = MAP_ROW - 1,
              COL_END = MAP_COL - 1;
    const string itemIndex = " ^X@=+-%";

    bool finish;
    int level;
};
#endif
