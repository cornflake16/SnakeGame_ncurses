#include "Stage.h"
/************************************************
    @file Main.cpp
    @author 윤낙원(Nakwon Yun), 김현민(Hyunmin Kim)
    @version 1.0 06/26/2020
************************************************/
int main()
{
    Stage view = Stage();
    string game;
    while(1)
    {
        game = view.menu();
        clear();
        if(game == "PLAY")
            view.play();
        else if(game == "HELP")
            view.help();
        else if(game == "OPTION")
            view.option();
        else
            break;
    }
    return 0;
}
