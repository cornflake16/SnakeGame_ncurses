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
    do
    {
        view.drawMap(map);
    } while ((key = getch()) != 27);
    endwin();
    return 0;
}
