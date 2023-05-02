#include"main.h"


int main(int argc, char *argv[])
{
	initAll();

	while (1)
    {
        // check win
        if(app.win){
            if(victoryTimer > 0){
                app.delegate.logic();
                app.delegate.draw();
            }
            if(victoryTimer-- <= 0)
            drawVictory();
            doInput();
            if(app.again) resetStage();
        }else
        {

        //check gameover
	    if(app.gameover)
        {
            if(gameoverTimer > 0){
                app.delegate.logic();
                app.delegate.draw();
            }
            if(--gameoverTimer <= 0)
        	{
        	    drawGameOver();
        	}
            doInput();
            if(app.again){
                resetStage();
            }
        }
        else {
		doInput();

		// check game pause
        if(!app.pause){
            app.delegate.logic();
            app.delegate.draw();
        }else {
            app.delegate.draw();
            viewPauseStage();
            }
        }
        }
		SDL_RenderPresent(app.renderer);
        SDL_Delay(18);
	}
	return 0;
}
