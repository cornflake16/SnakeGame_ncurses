#include "Stage.h"

Stage::Stage()
{
    initscr();
    keypad(stdscr, 1);
    curs_set(0);
    resize_term(NLINES, NCOLS);
    cbreak();
    noecho();
    start_color();

    if (has_colors() == FALSE) //사용자의 터미널(커맨드)에서 색상을 지원하지 않는다면 종료
    {
        endwin();
        printf("Your terminal does not support color\n");
        exit(1);
    }
    if (init_color(COLOR_BLUE, 0, 0, 300) == ERR) //터미널에서 색상이 정상적으로 바뀌는지 여부확인
    {
        printw("Your terminal cannot change the color definitions\n");
        printw("press any key to continue...\n");
        getch();
        move(0, 0);
    }
    init_pair(EMPTY, COLOR_WHITE, COLOR_BLACK);          //0(빈칸):  하양, 검정
    init_pair(WALL, COLOR_BLACK, COLOR_WHITE);           //1(벽): 검정, 하양
    init_pair(IMMUNE_WALL, COLOR_MAGENTA, COLOR_YELLOW); //2(기둥): 분홍, 노랑
    init_pair(SNAKE_HEAD, COLOR_YELLOW, COLOR_BLACK);    //3(뱀 머리): 노랑, 검정
    init_pair(SNAKE_BODY, COLOR_CYAN, COLOR_BLUE);       //4(뱀 몸): 형광, 파랑
    init_pair(GROWTH_ITEM, COLOR_YELLOW, COLOR_RED);     //5(+ 아이템): 노랑, 빨강
    init_pair(POISON_ITEM, COLOR_RED, COLOR_MAGENTA);    //6(- 아이템) 빨강, 분홍
    init_pair(GATE, COLOR_CYAN, COLOR_CYAN);             //7(목표+캐릭터):  형광, 형광
    refresh();
}
Stage::~Stage()
{
    delwin(win);
    delwin(game);
    int i, j;
    for (i = 0; i < STAGE_NUM; i++)
    {
        for (j = 0; j < MAP_ROW; j++)
            delete[] stage[i][j];
        delete[] stage[i];
    }
    delete[] stage;
}

void Stage::drawMission()
{
}

void Stage::setMap(int ***&stage)
{
    int i, j, k;
    stage = new int **[STAGE_NUM];
    for (i = 0; i < STAGE_NUM; i++)
    {
        stage[i] = new int *[MAP_ROW];
        for (j = 0; j < MAP_ROW; j++)
        {
            stage[i][j] = new int[MAP_COL];
        }
    }

    for (i = 0; i < STAGE_NUM; i++)
    {
        for (j = 0; j < MAP_ROW; j++)
        {
            for (k = 0; k < MAP_COL; k++)
            {
                if (!j || !k || j == MAP_ROW - 1 || k == MAP_COL - 1)
                    stage[i][j][k] = WALL;
                else
                    stage[i][j][k] = EMPTY;
            }
        }
        stage[i][0][0] = IMMUNE_WALL;
        stage[i][0][MAP_COL - 1] = IMMUNE_WALL;
        stage[i][MAP_ROW - 1][0] = IMMUNE_WALL;
        stage[i][MAP_ROW - 1][MAP_COL - 1] = IMMUNE_WALL;
    }
}

int **Stage::copyMap(int nStage)
{
    int **m = new int *[MAP_ROW];
    for (int i = 0; i < MAP_COL; i++)
        m[i] = new int[MAP_COL];
    for (int i = 0; i < MAP_ROW; i++)
    {
        for (int j = 0; j < MAP_COL; j++)
        {
            m[i][j] = stage[nStage][i][j];
        }
    }
    return m;
}

void Stage::drawMap(int srcY, int srcX, int **map)
{
    string itemIndex = ".^X@=+-%";
    int height = (NLINES - 1) / 1.5, width = (NCOLS - 1) / 1.5;

    win = newwin(NLINES-1, NCOLS-1, 0, 0);
    box(win, 0, 0);

    game = newwin(height, width, 6, 5);
    for (int i = 0; i < MAP_ROW; i++)
    {
        for (int j = 0; j < MAP_COL*3; j+=3)
        {
            int index = map[i][j/3];
            wattron(game, COLOR_PAIR(index));
            mvwaddch(game, i, j, ' ');
            mvwaddch(game, i, j+1, itemIndex[index]);
            mvwaddch(game, i, j+2, ' ');
            wattroff(game, COLOR_PAIR(index));
        }
        printw("\n");
    }
    score = newwin(18, 30, 1, 84);
    box(score, 0, 0);
    mvwprintw(score, 0, 10, "[ SCORE ]");

    mission = newwin(18, 30, 20, 84);
    box(mission, 0, 0);
    mvwprintw(mission, 0, 9, "[ MISSION ]");

    wrefresh(win);
    wrefresh(game);
    wrefresh(score);
    wrefresh(mission);
}

void Stage::pause()
{
}

void Stage::resume()
{
}
void Stage::Move(int direction)
{
}
