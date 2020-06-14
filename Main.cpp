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
    // view.makeSnake();
    do
    {
      view.Move(key,map);
      view.drawMap(map);
    } while ((key = getch()) != 27);
    endwin();
    return 0;
}
