#include "Stage.h"
int key, t, n;

int main()
{
    Stage view = Stage();
    view.setMap(view.stage);
    for (int i = 0; i < view.getStageNum(); i++)
    {
        t = n = 0;
        mvprintw(3, 23, "[ Stage %d / %d ]", i + 1, view.getStageNum());
        view.copyMap(i);
        view.setMission();
        view.makeSnake();
        view.appearGate();
        view.drawMap();
        while (1)
        {
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
            view.moveSnake();
            if (view.chkEnter) // 게이트에 진입 후, 꼬리 부분까지 진출 성공 시, 문 재생성
            {
                if (++n >= view.stat[0])
                {
                    view.disappearGate();
                    view.appearGate();
                    n = 0;
                    view.chkEnter = FALSE;
                }
            }
            if (++t % 50 == 0) // 5초마다 아이템 재생성 (쓰레드 구현이 아니므로, 미세한 오차가 존재)
            {
                view.disappearItem();
                view.appearItem();
            }
            if (view.stat[0] < 3) // 뱀의 길이가 3미만일 경우, 게임 오버
            {
                view.Gameover();
            }
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
            view.drawMap();
            timeout(100); // 0.1s 딜레이
        }
    }
    endwin();
    return 0;
}
