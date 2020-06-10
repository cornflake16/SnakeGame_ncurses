#include "Stage.h"

int main()
{
    Stage view = Stage();
    view.setMap(view.stage);
    while (1)
    {
        int **map = view.copyMap(0);
        int key = getch();
        view.drawMap(view.getMapRow(), view.getMapCol(), map);
        if (key == 27)
            break;
    }
    endwin();
    return 0;
}
