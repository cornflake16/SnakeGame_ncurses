#include "Stage.h"
WINDOW *create_newwin(int height, int width, int starty, int startx);
Stage::Stage()
{
    finish = false;
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
}
Stage::~Stage()
{
    delwin(mission);
    delwin(score);
    delwin(game);
    delwin(win);
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

void Stage::drawMap(int **map)
{
    string itemIndex = " ^X@=+-%";
    int height = NLINES / 1.5 - 1, width = NCOLS / 1.5 - 23;

    game = newwin(height, width, 7, 11);
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
    drawBorders();
    wrefresh(game);
    mvprintw(3, 80, "[ SCORE ]");
    mvprintw(20, 79, "[ MISSION ]");
}

void Stage::appearItem(int **&map)
{
    int nItem = rand() % 3 + 1;
    pair<int, int> item[nItem];
    int row, col;
    for (int i = 0; i < sizeof(item) / sizeof(item[0]); i++)
    {
        int itemType = rand() % 2 + 5;
        while (1)
        {
            row = rand() % MAP_ROW;
            col = rand() % MAP_COL;
            if (map[row][col] == EMPTY)
                break;
        }
        item[i].first = row;
        item[i].second = col;
        map[item[i].first][item[i].second] = itemType;
    }
}

void Stage::appearGate(int **&map)
{
    pair<int, int> gate[2];
    int n, row, col;
    int y, x;
    for (int i = 0; i < 2; i++)
    {
        while (1)
        {
            n = rand() % 4;
            row = rand() % MAP_ROW;
            col = rand() % MAP_COL;
            switch (n)
            {
            case 0: // 상단 벽
                y = 0;
                x = col;
                break;
            case 1: // 좌측
                y = row;
                x = 0;
                break;
            case 2: // 우측
                y = row;
                x = MAP_COL - 1;
                break;
            case 3: // 하단
                y = MAP_ROW - 1;
                x = col;
                break;
            }
            if (map[y][x] == WALL)
                break;
        }
        gate[i].first = y;
        gate[i].second = x;
        map[gate[i].first][gate[i].second] = GATE;
        if(i == 0){
          gate1 = new Something(y,x,GATE);
        }
        if(i == 1){
          gate2 = new Something(y,x,GATE);
        }
    }
}

void Stage::pause()
{
}

void Stage::resume()
{
}

void Stage::Move(int direction,int** map)
{
  map[Bam->y][Bam->x] = 0;
  Something* q = Bam;
  Something* p = Bam->link;
  while(p->link != NULL){
    q->x = p->x; q->y = p->y;
    q = p;
    p = p->link;
  }
  if(direction == 65 || direction == 97){
    map[p->y][p->x] = q->who;
    q->x = p->x; q->y = p->y;
    p->x -=1;
  }
  else if(direction == 87 || direction == 119){
    map[p->y][p->x] = q->who;
    q->x = p->x; q->y = p->y;
    p->y -=1;
  }
  else if(direction == 68 || direction == 100){
    map[p->y][p->x] = q->who;
    q->x = p->x; q->y = p->y;
    p->x +=1;
  }
  else if(direction == 83 || direction == 115){
    map[p->y][p->x] = q->who;
    q->x = p->x; q->y = p->y;
    p->y +=1;
  }
  if(map[p->y][p->x] == 5 || map[p->y][p->x] == 6){
    EatItem(map[p->y][p->x],direction,map);
  }
  if(map[p->y][p->x] == 1 || map[p->y][p->x] == 2 || map[p->y][p->x] == 4){
    Gameover();
  }
  if(map[p->y][p->x] == GATE){
    Gate(p,map,direction);
  }
  map[p->y][p->x] = p->who;
}

void Stage::drawBorders()
{
    refresh();
    create_newwin(NLINES - 1, NCOLS - 1, 0, 0);
    create_newwin(16, 30, 3, 70);
    create_newwin(16, 30, 20, 70);
}

WINDOW *create_newwin(int height, int width, int starty, int startx)
{
    WINDOW *local_win;

    local_win = newwin(height, width, starty, startx);
    box(local_win, 0, 0);

    wrefresh(local_win);
    return local_win;
}

void Stage::makeSnake(int **map){
  Body = 3;
  string itemIndex = " ^X@=+-%";
  int row = 13;
  int col = 26;
  Bam = new Something(row,col--,SNAKE_BODY);
  Something* p = new Something(row,col--,SNAKE_BODY);
  Bam -> link = p;
  p = new Something(row,col--,SNAKE_HEAD);
  Bam -> link -> link = p;
  map[Bam->y][Bam->x] = Bam->who;
  p = Bam-> link;
  map[p->y][p->x] = p->who;
  p = p->link;
  map[p->y][p->x] = p->who;
}

void Stage::EatItem(int item,int dir,int** map){
  if(item == 5){
    if(Body == 10){
      return;
    }
    Something* p = new Something(Bam->y,Bam->x,4);
    if(dir == 65)
      p->x++;
    else if(dir == 87)
      p->y++;
    else if(dir == 68)
      p->x--;
    else if(dir == 83)
      p->y--;
    p->link = Bam;
    Bam = p;
    map[Bam->y][Bam->x] = Bam->who;
    Body++;
  }
  else if(item == 6){
    map[Bam->y][Bam->x] = 0;
    Bam = Bam->link;
    Body--;
  }
}

void Stage::Gameover(){
  finish = true;
}

void Stage::Gate(Something* head,int** map,int dir){
  int root;
  if(gate1->x == head->x && gate1->y == head->y){
    if(gate2->x == 0){
      head->x = 1; head->y = gate2->y;
    }
    else if(gate2->x == 49){
      head->x = 48; head->y = gate2->y;
    }
    else if(gate2->y == 0){
      head->x = gate2->x; head->y = 1;
    }
    else if(gate2->y == 24){
      head->x = gate2->x; head->y = 23;
    }
    else{// 중간벽에 게이트가 있을시
      root = findRoot(gate2,dir,map);
      if(root == 65){
        head->x = gate2->x-1;
        head->y = gate2->y;
      }
      else if(root == 87){
        head->x = gate2->x;
        head->y = gate2->y-1;
      }
      else if(root == 68){
        head->x = gate2->x+1;
        head->y = gate2->y;
      }
      else if(root == 83){
        head->x = gate2->x;
        head->y = gate2->y+1;
      }
    }
  }
  else if(gate2->x == head->x && gate2->y == head->y){
    if(gate1->x == 0){
      head->x = 1; head->y = gate1->y;
    }
    else if(gate1->x == 49){
      head->x = 48; head->y = gate1->y;
    }
    else if(gate1->y == 0){
      head->x = gate1->x; head->y = 1;
    }
    else if(gate1->y == 24){
      head->x = gate1->x; head->y = 23;
    }
    else{ // 중간벽에 게이트가 있을시
      root = findRoot(gate1,dir,map);
      if(root == 65){
        head->x = gate1->x-1;
        head->y = gate1->y;
      }
      else if(root == 87){
        head->x = gate1->x;
        head->y = gate1->y-1;
      }
      else if(root == 68){
        head->x = gate1->x+1;
        head->y = gate1->y;
      }
      else if(root == 83){
        head->x = gate1->x;
        head->y = gate1->y+1;
      }
    }
  }
}

int Stage::findRoot(Something* gate,int dir,int** map){
  for(int i =0;i<4;i++){
    if(dir == 65){
      if(map[gate->y][gate->x -1] == 0) return dir;
      else dir = 87;
    }
    else if(dir == 87){
      if(map[gate->y -1][gate->x] == 0) return dir;
      else dir = 68;
    }
    else if(dir == 68){
      if(map[gate->y][gate->x + 1]== 0) return dir;
      else dir = 83;
    }
    else if(dir == 83){
      if(map[gate->y +1][gate->x] == 0) return dir;
      else dir = 65;
    }
  }
}
