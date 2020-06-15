#include "Stage.h"
int **map;
int key, t = 0;
int dir = LEFT;

int main()
{
    Stage view = Stage();
    view.setMap(view.stage);
    for (int i = 0; i < view.getStageNum(); i++)
    {
        mvprintw(3, 23, "[ Stage %d / %d ]", i + 1, view.getStageNum());
        map = view.copyMap(i);
        view.setMission();
        view.appearGate(map);
        view.makeSnake(map);
        pair<int, int> nItems = view.numOfItems(map);
        while (1)
        {
            if (!(++t % 10) && (nItems.first + nItems.second) < 4)
                view.appearItem(map);
            if (view.stat[0] < 3)
                view.Gameover();
            view.drawMap(map);
            switch (key = getch())
            {
            case LEFT:
                if (dir != RIGHT)
                    dir = LEFT;
                break;
            case UP:
                if (dir != DOWN)
                    dir = UP;
                break;
            case RIGHT:
                if (dir != LEFT)
                    dir = RIGHT;
                break;
            case DOWN:
                if (dir != UP)
                    dir = DOWN;
                break;
            case ESC:
                endwin();
                return 0;
            }
            view.move(dir, map);
            if (view.isMissionClear())
            {
                view.alert(0, 2, "Stage Clear!");
                break;
            }
            if (view.checkfinish())
                goto end;
            timeout(100);
        };
    }

end:
    view.alert(0, 2, "Game Over!");
    endwin();
    return 0;
}
