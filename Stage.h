#ifndef __STAGE__
#define __STAGE__
#include <ncurses.h>
#include <iostream>

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

    Stage();
    ~Stage();
    int getStageNum() const { return STAGE_NUM; }
    int getMapRow() const { return MAP_ROW; }
    int getMapCol() const { return MAP_COL; }
    int getNlines() const { return NLINES; }
    int getNcols() const { return NCOLS; }
    void setMap(int ***&stage);
    int **copyMap(int nStage);
    void drawMap(int scrX, int scrY, int **map);

    void setMission();
    void drawMission();
    void pause();
    void resume();

    void Move(int direction);
    void makeItem();
    void makeGate();
    void isMissionClear();

private:
    const int STAGE_NUM = 4; //스테이지 개수
    const int MAP_ROW = 25,
              MAP_COL = 25; //맵 세로, 가로 길이
    const int NLINES = 40,
              NCOLS = 120;
};
#endif
