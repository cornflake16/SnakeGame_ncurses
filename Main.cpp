#include "Stage.h"
int **map;
int key, t = 0;

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
        view.Setdir(LEFT);
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
                if (view.Getdir() != RIGHT)
                    view.Setdir(LEFT);
                break;
            case UP:
                if (view.Getdir() != DOWN)
                    view.Setdir(UP);
                break;
            case RIGHT:
                if (view.Getdir() != LEFT)
                    view.Setdir(RIGHT);
                break;
            case DOWN:
                if (view.Getdir() != UP)
                    view.Setdir(DOWN);
                break;
            case 29:
                endwin();
                return 0;
            }
            view.move(map);
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
