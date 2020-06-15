#include "Stage.h"
int **map;
int key, t = 0;

int main()
{
    Stage view = Stage();
    view.setMap(view.stage);
    for(int i=0; i<view.getStageNum(); i++)
    {
        mvprintw(3, 23, "[ Stage %d / %d ]", i+1, view.getStageNum());
        map = view.copyMap(i);
        view.setMission();
        view.appearGate(map);
        view.makeSnake(map);
        pair<int, int> nItems = view.numOfItems(map);
        while(1)
        {
            if (!(++t % 10) && (nItems.first + nItems.second) < 4)
                view.appearItem(map);
            if (view.stat[0] < 3)
                view.Gameover();
            view.move(key, map);
            view.drawMap(map);
            if(view.isMissionClear())
            {
                view.alert(0, 2, "Stage Clear!");
                break;
            }
            if((key=getch()) == 27 || view.checkfinish())
                goto end;
            timeout(500);
        };
    }
    
    end:
    view.alert(0, 2, "Game Over!");
    endwin();
    return 0;
}
