#include "Stage.h"

Stage::Stage()
{
    initscr();
    curs_set(0);               //커서 비활성화
    if (has_colors() == FALSE) //사용자의 터미널(커맨드)에서 색상을 지원하지 않는다면 종료
    {
        endwin();
        printf("Your terminal does not support color\n");
        exit(1);
    }
    start_color();                                // Color 사용 선언
    if (init_color(COLOR_BLUE, 0, 0, 300) == ERR) //터미널에서 색상이 정상적으로 바뀌는지 여부확인
    {
        printw("Your terminal cannot change the color definitions\n");
        printw("press any key to continue...\n");
        getch();
        move(0, 0);
    }
    init_pair(EMPTY, COLOR_WHITE, COLOR_BLACK);          //0(빈칸):  하양, 검정
    init_pair(WALL, COLOR_BLACK, COLOR_WHITE);           //1(벽): 검정, 노랑
    init_pair(IMMUNE_WALL, COLOR_MAGENTA, COLOR_YELLOW); //2(기둥): 분홍, 노랑
    init_pair(SNAKE_HEAD, COLOR_YELLOW, COLOR_BLACK);    //3(뱀 머리): 노랑, 검정
    init_pair(SNAKE_BODY, COLOR_CYAN, COLOR_BLUE);       //4(뱀 몸): 형광, 파랑
    init_pair(GROWTH_ITEM, COLOR_YELLOW, COLOR_RED);     //5(+ 아이템): 노랑, 빨강
    init_pair(POISON_ITEM, COLOR_RED, COLOR_MAGENTA);    //6(- 아이템) 빨강, 분홍
    init_pair(GATE, COLOR_CYAN, COLOR_CYAN);             //7(목표+캐릭터):  형광, 형광
}
