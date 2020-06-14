#include "Stage.h"

int **map;
int key;
pair<int, int> gate[2];
int main()
{
    srand((unsigned)time(0));
    Stage view = Stage();
    view.setMap(view.stage);
    map = view.copyMap(0);
    view.appearGate(map);
    view.appearItem(map);
    view.makeSnake(map);
    view.drawMap(map);
    while ((key = getch()) != 27)
    {
      if(view.checkfinish()) break;
      if(key == 65 || key == 87 || key == 68 || key == 83){
          view.Move(key,map);
      }
      if(view.checkBody() < 3) view.Gameover();
      view.drawMap(map);
    }
    endwin();
    return 0;
}
