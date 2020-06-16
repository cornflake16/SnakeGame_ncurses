#include "Stage.h"
int **map;
int key, t;

int main()
{
    Stage view = Stage();
    view.setMap(view.stage);
    for (int i = 0; i < view.getStageNum(); i++)
    {
        t = 0;
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
            view.drawMap(map);
            switch (key = getch())
            {
            case LEFT:
                if (view.dir != RIGHT)
                    view.dir = LEFT;
                break;
            case UP:
                if (view.dir != DOWN)
                    view.dir = UP;
                break;
            case RIGHT:
                if (view.dir != LEFT)
                    view.dir = RIGHT;
                break;
            case DOWN:
                if (view.dir != UP)
                    view.dir = DOWN;
                break;
            case ESC:
                endwin();
                return 0;
            }
            view.move(map);
            if (view.stat[0] < 3)
                view.Gameover();
            if (view.isMissionClear())
            {
                view.alert(0, 2, "Stage Clear!");
                break;
            }
            if (view.checkGameOver())
            {
                view.alert(0, 2, "Game Over!");
                endwin();
                return 0;
            }
            timeout(100);
        };
    }

end:
    endwin();
    return 0;
}
