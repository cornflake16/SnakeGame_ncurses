/************************************************
    @file Stage.h
    @author 윤낙원(Nakwon Yun), 김현민(Hyunmin Kim) 
    @version 1.0 06/26/2020
************************************************/
#ifndef __STAGE__
#define __STAGE__
#include <ncurses.h>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <vector>
#include <fstream>
#include "Something.h"

/*  
    CAUTION: IF YOU CHANGE THE DEFINED VALUES, 
    THE PROGRAM MAY BEHAVE ABNORMALLY.
    SO, DO NOT CHANGE THE VALUES OF BELOW.
*/

// Shortcuts definition
#define UP KEY_UP
#define DOWN KEY_DOWN
#define RIGHT KEY_RIGHT
#define LEFT KEY_LEFT
#define ENTER 10
#define ESC 27
#define PAUSE 112
#define RESUME 114

// items index definition
#define EMPTY 0
#define WALL 1
#define IMMUNE_WALL 2
#define SNAKE_HEAD 3
#define SNAKE_BODY 4
#define GROWTH_ITEM 5
#define POISON_ITEM 6
#define GATE 7

using namespace std;

class Stage
{
public:
    // class constructor & destructor
    Stage();
    ~Stage();

    // function about fixing Screen size.
    void screenLock();

    // functions about Menu
    string menu();
    void play();
    void help();
    void option();

    // functions about getting Stage & Map size
    int getStageNum() const { return STAGE_NUM; }
    int getMapRow() const { return MAP_ROW; }
    int getMapCol() const { return MAP_COL; }

    // functions about Map
    void setMap();
    void copyMap(int nStage);
    void drawMap();

    // functions about Item & Gate generation
    void appearItem();
    void appearGate();
    void disappearItem();
    void disappearGate();

    // functions about Snake behavior
    void makeSnake();
    void moveSnake();
    void enterGate(Something *head);
    int findRoot(Something *gate);
    void eatItem(int item);

    // functions about Game progress
    void setMission();
    bool isMissionClear();
    bool checkGameOver() { return finish; }
    void gameOver();
    void alert(int posY, int posX, const string msg, bool stopFlag);

private:
    // window(ncurses) variables
    WINDOW *game, *score, *mission, *info;
    WINDOW *manual, *description, *scrollBar;

    // Snake state variable
    int stat[4];

    // mission variables
    char chkMission[4];
    int statMission[4];

    // struct variables about Snake
    Something *Bam;
    Something *gate1;
    Something *gate2;

    // const variables about map & snake index
    const int STAGE_NUM = 4,
              MAP_ROW = 25,
              MAP_COL = 50,
              ROW_END = MAP_ROW - 1,
              COL_END = MAP_COL - 1;
    const string itemIndex = "  X0O+- ";

    // variables about stage & map
    int ***stage, **map;

    // variables about snake
    int dir, y, x,
        menuLastFocus, optLastFocus,
        level, speed,
        nTime;

    // variables about manual & option 
    string title, menuTitle, shorTitle;
    string menuTxt[4], shorTxt[7];
    int sizeY, sizeX,
        startY, startX;
    int desSizeY, desSizeX,
        desStartY, desStartX;
    int txtLines, hidTxtLen, scrollBarLen;

    string manualTitle;
    vector<string> manualTxt;

    vector<pair<int, int>> itemPos, gatePos;
    bool chkEnter, finish;
};
#endif
