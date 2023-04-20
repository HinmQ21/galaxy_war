#include"main.h"


int main(int argc, char *argv[])
{
    srand(time(NULL));

	initSDL();

	initGame();

    initTitle();

	while (1)
	{
        SDL_ShowCursor(0);
	    if(app.gameover){
            SDL_RenderClear(app.renderer);
        	drawBackground();
        	drawGameOver();
        	drawYesNo();
        	drawMouse();
        	doYesNo();
            if(app.again){
                app.gameover = 0;
                resetStage();
                app.again=0;
            }
		}

		doInput();

        if(!app.pause && !app.gameover){
		app.delegate.logic();
		app.delegate.draw();
        }else if(app.pause && app.start){
            app.delegate.draw();
            drawContinue();
            drawQuit();
            drawMouse();
            doQuit();
            doContinue();
        }
		SDL_RenderPresent(app.renderer);

        SDL_Delay(18);
	}
	return 0;
}
