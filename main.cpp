#include"main.h"


int main(int argc, char *argv[])
{
	initAll();

	while (1)
    {
	    if(app.gameover)
        {
            if(--gameoverTimer <= 0)
        	drawGameOver();
            doInput();
            if(app.again){
                resetStage();
            }
        }
        else {
		doInput();

        if(!app.pause){
            app.delegate.logic();
            app.delegate.draw();
        }else {
            app.delegate.draw();
            drawContinue();
            drawQuit();
            drawMouse();
            doQuit();
            doContinue();
            }
        }
		SDL_RenderPresent(app.renderer);
        SDL_Delay(18);
	}
	return 0;
}
