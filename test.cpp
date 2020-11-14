#include <ncurses.h>
#include <iostream>

using namespace std;


struct Something{
  int x;
  int y; // 10을 곱함
  char who;
  Something* link;
  Something(int row,int col,char what){
    who = what;
    y = row;
    x = col;
    link = NULL;
  }
};

void make_snake(WINDOW* game,int col,int row){//x와 y는 뱀소환 위치
  Something* bam = new Something(row,col++,'3');
  Something* p = bam;
  for(int i =0;i<3;i++){
    Something* body = new Something(row,col++,'4');
    p->link = body;
    p = body;
  }
  cout << bam->who << endl;
  while(bam->link != NULL){
    mvwprintw(game,bam->y,bam->x,bam->who);
    bam = bam->link;
  }
}

void make_map(WINDOW* game,int col,int row){
  Something* wall = new Something(row,col++,'2');
  Something* p = wall;
  while(row != 0 ||col != 0){//map의 크기가 25일때
    if(row == 0 && col != 25){
      Something* next = new Something(row,col++,'2');
      p->link = next;
      p = next;
    }
    else if(col == 25 && row != 25){
      Something* next = new Something(row++,col,'2');
      p->link = next;
      p = next;
    }
    else if(row == 25 && col != 0){
      Something* next = new Something(row,col--,'2');
      p->link = next;
      p = next;
    }
    else{// row == 0;
      Something* next = new Something(row--,col,'2');
      p->link = next;
      p = next;
    }
  }
  while(wall->link != NULL){
    mvwprintw(game,wall->y,wall->x,wall->who);
    wall = wall->link;
  }
}

int main(){
  WINDOW *game;
  WINDOW *score;
  WINDOW *mission;

  initscr();
  resize_term(30,60);
  start_color();
  init_pair(2,COLOR_GREEN,COLOR_BLACK);
  init_pair(1,COLOR_WHITE,COLOR_RED);

  border('|','|','-','-','+','+','+','+');
  refresh();

  game = newwin(25,25,2,2);
  make_snake(game,12,12);
  make_map(game,0,0);
  wrefresh(game);

  score = newwin(8,15,3,40);

  wborder(score,'|','|','-','-','+','+','+','+');
  wrefresh(score);

  mission = newwin(7,15,15,40);

  wborder(mission,'|','|','-','-','+','+','+','+');
  wrefresh(mission);

  getch();
  endwin();
  return 0;

}
