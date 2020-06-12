#include "Stage.h"
int **map;
int main()
{
    Stage view = Stage();
    view.setMap(view.stage);
    map = view.copyMap(0);
    while (1)
    {
        int key = getch();
        view.drawMap(view.getMapRow(), view.getMapCol(), map);
        if (key == 27)
            break;
    }
    endwin();
    return 0;
}
