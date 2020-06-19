#include "Stage.h"
Stage::Stage()
{
    level = 0;
    srand((unsigned)time(0));
    initscr();
    resize_term(NLINES, NCOLS);
    keypad(stdscr, TRUE);
    curs_set(0);
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
        moveSnake();
    }
    init_pair(EMPTY, COLOR_WHITE, COLOR_BLACK);          //0(빈칸):  하양, 검정
    init_pair(WALL, COLOR_BLACK, COLOR_WHITE);           //1(벽): 검정, 하양
    init_pair(IMMUNE_WALL, COLOR_MAGENTA, COLOR_YELLOW); //2(기둥): 분홍, 노랑
    init_pair(SNAKE_HEAD, COLOR_YELLOW, COLOR_BLACK);    //3(뱀 머리): 노랑, 검정
    init_pair(SNAKE_BODY, COLOR_CYAN, COLOR_BLUE);       //4(뱀 몸): 형광, 파랑
    init_pair(GROWTH_ITEM, COLOR_YELLOW, COLOR_RED);     //5(+ 아이템): 노랑, 빨강
    init_pair(POISON_ITEM, COLOR_RED, COLOR_MAGENTA);    //6(- 아이템) 빨강, 분홍
    init_pair(GATE, COLOR_CYAN, COLOR_CYAN);             //8(목표+캐릭터):  형광, 형광
}

Stage::~Stage()
{
    delwin(mission);
    delwin(score);
    delwin(game);
    endwin();
}

void Stage::setMap()
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
                if (!j || !k || j == ROW_END || k == COL_END)
                    stage[i][j][k] = WALL;
                else
                    stage[i][j][k] = EMPTY;
            }
        }
        stage[i][0][0] = IMMUNE_WALL;
        stage[i][0][COL_END] = IMMUNE_WALL;
        stage[i][ROW_END][0] = IMMUNE_WALL;
        stage[i][ROW_END][COL_END] = IMMUNE_WALL;
        if (i == 1)
        {
            for (int z = 10; z < 40; z++)
                stage[i][7][z] = WALL;
            for (int z = 10; z < 40; z++)
                stage[i][MAP_ROW - 7][z] = WALL;
        }
        if (i == 2)
        {
            for (int z = 5; z < 20; z++)
                stage[i][z][MAP_COL - 15] = WALL;
            for (int z = 5; z < 20; z++)
                stage[i][z][15] = WALL;
        }
        if (i == 3)
        {
            for (int z = 10; z < 40; z++)
            {
                if (z > 22 && z < 27)
                    continue;
                stage[i][7][z] = WALL;
            }
            for (int z = 10; z < 40; z++)
            {
                if (z > 22 && z < 27)
                    continue;
                stage[i][MAP_ROW - 7][z] = WALL;
            }
            for (int z = 5; z < 20; z++)
            {
                if (z > 10 && z < 14)
                    continue;
                if(stage[i][z][MAP_COL - 15] == WALL)
                  stage[i][z][MAP_COL - 15] = IMMUNE_WALL;
                else
                  stage[i][z][MAP_COL - 15] = WALL;
            }
            for (int z = 5; z < 20; z++)
            {
                if (z > 10 && z < 14)
                    continue;
                if(stage[i][z][15] == WALL)
                  stage[i][z][15] = IMMUNE_WALL;
                else
                  stage[i][z][15] = WALL;
            }
        }
    }
}

void Stage::copyMap(int nStage)
{
    level++;
    map = new int *[MAP_ROW];
    for (int i = 0; i < MAP_COL; i++)
        map[i] = new int[MAP_COL];
    for (int i = 0; i < MAP_ROW; i++)
    {
        for (int j = 0; j < MAP_COL; j++)
            map[i][j] = stage[nStage][i][j];
    }
}

void Stage::drawMap()
{
    game = newwin(MAP_ROW, MAP_COL, 5, 6);
    for (int i = 0; i < MAP_ROW; i++)
    {
        for (int j = 0; j < MAP_COL; j++)
        {
            int index = map[i][j];
            wattron(game, COLOR_PAIR(index));
            mvwaddch(game, i, j, itemIndex[index]);
            wattroff(game, COLOR_PAIR(index));
        }
        printw("\n");
    }

    score = newwin(16, 30, 1, 64);
    box(score, 0, 0);
    mvwprintw(score, 0, 10, "[ SCORE ]");
    mvwprintw(score, 3, 5, "B: %d / 10", stat[0]);
    mvwprintw(score, 6, 5, "+: %d", stat[1]);
    mvwprintw(score, 9, 5, "-: %d", stat[2]);
    mvwprintw(score, 12, 5, "G: %d", stat[3]);

    mission = newwin(16, 30, 18, 64);
    box(mission, 0, 0);
    mvwprintw(mission, 0, 9, "[ MISSION ]");
    mvwprintw(mission, 3, 5, "B: %d ( %c )", statMission[0], chkMission[0]);
    mvwprintw(mission, 6, 5, "+: %d ( %c )", statMission[1], chkMission[1]);
    mvwprintw(mission, 9, 5, "-: %d ( %c )", statMission[2], chkMission[2]);
    mvwprintw(mission, 12, 5, "G: %d ( %c )", statMission[3], chkMission[3]);

    refresh();
    wrefresh(game);
    wrefresh(score);
    wrefresh(mission);
}

void Stage::setMission()
{
    finish = chkEnter = FALSE;
    dir = LEFT;
    memset(stat, 0, sizeof(stat));
    memset(statMission, 0, sizeof(statMission));
    memset(chkMission, ' ', sizeof(chkMission));
    statMission[0] = rand() % 5 + 6; // 뱀 길이: 6~10
    statMission[1] = rand() % 5 + 4; // 증가 아이템 획득 횟수: 4~8
    statMission[2] = rand() % 4 + 3; // 감소 아이템 획득 횟수: 3~6
    statMission[3] = rand() % 5 + 1; // 게이트 진출 횟수: 1~5
}

bool Stage::isMissionClear()
{
    int count = 0;
    for (int i = 0; i < 4; i++)
    {
        if (stat[i] >= statMission[i])
        {
            chkMission[i] = 'v';
            count++;
        }
        else if (!i)
            chkMission[i] = ' ';
    }
    if (count == 4)
        return TRUE;
    return FALSE;
}

void Stage::appearItem()
{
    int appearNum = rand() % 3 + 1;
    for (int i = 0; i < appearNum; i++)
    {
        int itemType = rand() % 2 + GROWTH_ITEM;
        if (stat[0] <= 3 || chkMission[2] == 'v')
            itemType = GROWTH_ITEM;
        while (1)
        {
            int y = rand() % (MAP_ROW - 2) + 1;
            int x = rand() % (MAP_COL - 2) + 1;
            if (map[y][x] == EMPTY)
            {
                map[y][x] = itemType;
                itemPos.push_back(make_pair(y, x));
                break;
            }
        }
    }
}

void Stage::appearGate()
{
    int n, y, x;
    for (int i = 0; i < 2; i++)
    {
        while (1)
        {
            n = rand() % (level ? 4 : 5);
            y = rand() % (MAP_ROW - 2) + 1;
            x = rand() % (MAP_COL - 2) + 1;
            switch (n)
            {
            case 0: // 상단 벽
                y = 0;
                break;
            case 1: // 좌측
                x = 0;
                break;
            case 2: // 우측
                x = COL_END;
                break;
            case 3: // 하단
                y = ROW_END;
                break;
            case 4: // 중간
                while (1)
                {
                    x = rand() % 30 + 10;
                    y = rand() % 15 + 5;
                    if (map[y][x] == WALL)
                        break;
                }
            }
            if (map[y][x] == WALL)
            {
                map[y][x] = GATE;
                gatePos.push_back(make_pair(y, x));
                break;
            }
        }
        if (i == 0)
            gate1 = new Something(y, x, GATE);
        if (i == 1)
            gate2 = new Something(y, x, GATE);
    }
}

void Stage::disappearItem()
{
    for (auto item : itemPos)
        map[item.first][item.second] = EMPTY;
    itemPos.clear();
}

void Stage::disappearGate()
{
    for (auto gate : gatePos)
        map[gate.first][gate.second] = WALL;
    gatePos.clear();
}

void Stage::makeSnake()
{
    stat[0] = 3;
    string itemIndex = " ^X@=+-%";
    int row = 13;
    int col = 26;
    Bam = new Something(row, col--, SNAKE_BODY);
    Something *p = new Something(row, col--, SNAKE_BODY);
    Bam->link = p;
    p = new Something(row, col--, SNAKE_HEAD);
    Bam->link->link = p;
    map[Bam->y][Bam->x] = Bam->who;
    p = Bam->link;
    map[p->y][p->x] = p->who;
    p = p->link;
    map[p->y][p->x] = p->who;
}

void Stage::moveSnake()
{
    if(map[Bam->y][Bam->x] != WALL)
      map[Bam->y][Bam->x] = EMPTY;

    Something *q = Bam;
    Something *p = q->link;
    while (p->link != NULL)
    {
        q->x = p->x;
        q->y = p->y;
        q = p;
        p = p->link;
    }
    if (dir == LEFT)
    {
        map[p->y][p->x] = q->who;
        q->x = p->x;
        q->y = p->y;
        p->x--;
    }
    else if (dir == UP)
    {
        map[p->y][p->x] = q->who;
        q->x = p->x;
        q->y = p->y;
        p->y--;
    }
    else if (dir == RIGHT)
    {
        map[p->y][p->x] = q->who;
        q->x = p->x;
        q->y = p->y;
        p->x++;
    }
    else if (dir == DOWN)
    {
        map[p->y][p->x] = q->who;
        q->x = p->x;
        q->y = p->y;
        p->y++;
    }
    if (map[p->y][p->x] == WALL || map[p->y][p->x] == SNAKE_BODY)
    {
        map[p->y][p->x] = IMMUNE_WALL;
        Gameover();
    }
    if (map[p->y][p->x] == GATE)
    {
        enterGate(p);
    }
    if (map[p->y][p->x] == GROWTH_ITEM || map[p->y][p->x] == POISON_ITEM)
    {
        eatItem(map[p->y][p->x]);
    }
    map[p->y][p->x] = p->who;
}

void Stage::eatItem(int item)
{
    if (item == GROWTH_ITEM)
    {
        if (stat[0] == 10)
            return;
        Something *p = new Something(Bam->y, Bam->x, SNAKE_BODY);
        if (Bam->x - Bam->link->x == 1)
            p->x++;
        else if (Bam->y - Bam->link->y == 1)
            p->y++;
        else if (Bam->x - Bam->link->x == -1)
            p->x--;
        else if (Bam->y - Bam->link->y == -1)
            p->y--;
        p->link = Bam;
        Bam = p;
        map[Bam->y][Bam->x] = Bam->who;
        stat[0]++;
        stat[1]++;
    }
    else if (item == POISON_ITEM)
    {
        map[Bam->y][Bam->x] = EMPTY;
        Bam = Bam->link;
        stat[0]--;
        stat[2]++;
    }
}

void Stage::Gameover()
{
    finish = true;
}

void Stage::alert(int color, int bkgdColor, const string msg)
{
    WINDOW *alert = newwin(7, msg.length()*2, 13, 20);
    box(alert, 0, 0);
    wattron(alert, COLOR_PAIR(color));
    wbkgd(alert, COLOR_PAIR(bkgdColor));
    mvwprintw(alert, 3, msg.length()/2, msg.c_str());
    wrefresh(alert);
    usleep(1750000);
    clear();
}

void Stage::enterGate(Something *head)
{
    chkEnter = TRUE;
    if (gate1->x == head->x && gate1->y == head->y)
    {
        if (gate2->x == 0)
        {
            head->x = 1;
            head->y = gate2->y;
            dir = RIGHT;
        }
        else if (gate2->x == COL_END)
        {
            head->x = COL_END - 1;
            head->y = gate2->y;
            dir = LEFT;
        }
        else if (gate2->y == 0)
        {
            head->x = gate2->x;
            head->y = 1;
            dir = DOWN;
        }
        else if (gate2->y == ROW_END)
        {
            head->x = gate2->x;
            head->y = ROW_END - 1;
            dir = UP;
        }
        // 중간벽에 게이트가 있을시
        findRoot(gate2);
        if (dir == LEFT)
        {
            head->x = gate2->x - 1;
            head->y = gate2->y;
        }
        else if (dir == UP)
        {
            head->x = gate2->x;
            head->y = gate2->y - 1;
        }
        else if (dir == RIGHT)
        {
            head->x = gate2->x + 1;
            head->y = gate2->y;
        }
        else if (dir == DOWN)
        {
            head->x = gate2->x;
            head->y = gate2->y + 1;
        }
    }
    else if (gate2->x == head->x && gate2->y == head->y)
    {
        if (gate1->x == 0)
        {
            head->x = 1;
            head->y = gate1->y;
            dir = RIGHT;
        }
        else if (gate1->x == COL_END)
        {
            head->x = COL_END - 1;
            head->y = gate1->y;
            dir = LEFT;
        }
        else if (gate1->y == 0)
        {
            head->x = gate1->x;
            head->y = 1;
            dir = DOWN;
        }
        else if (gate1->y == ROW_END)
        {
            head->x = gate1->x;
            head->y = ROW_END - 1;
            dir = UP;
        }
        // 중간벽에 게이트가 있을시
        findRoot(gate1);
        if (dir == LEFT)
        {
            head->x = gate1->x - 1;
            head->y = gate1->y;
        }
        else if (dir == UP)
        {
            head->x = gate1->x;
            head->y = gate1->y - 1;
        }
        else if (dir == RIGHT)
        {
            head->x = gate1->x + 1;
            head->y = gate1->y;
        }
        else if (dir == DOWN)
        {
            head->x = gate1->x;
            head->y = gate1->y + 1;
        }
    }
    stat[3]++;
}

int Stage::findRoot(Something *gate)
{
    for (int i = 0; i < 4; i++)
    {
        if (dir == LEFT)
        {
            if (map[gate->y][gate->x - 1] == EMPTY)
                return dir;
            else
                dir = KEY_UP;
        }
        else if (dir == KEY_UP)
        {
            if (map[gate->y - 1][gate->x] == EMPTY)
                return dir;
            else
                dir = RIGHT;
        }
        else if (dir == RIGHT)
        {
            if (map[gate->y][gate->x + 1] == EMPTY)
                return dir;
            else
                dir = DOWN;
        }
        else if (dir == DOWN)
        {
            if (map[gate->y + 1][gate->x] == EMPTY)
                return dir;
            else
                dir = LEFT;
        }
    }
    return dir;
}
