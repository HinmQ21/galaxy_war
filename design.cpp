#include "design.h"

extern void doStarfield();
extern void drawBackground();
extern void drawStarfield();

static void logic();
static void draw();
static void drawLogo();
void drawHelpScreen();
void doHelp();
void doBack();

static SDL_Texture* logoTexture;
static SDL_Texture* startbut1;
static SDL_Texture* startbut2;
static SDL_Texture* exitbut1;
static SDL_Texture* exitbut2;
static SDL_Texture* contibut1;
static SDL_Texture* contibut2;
static SDL_Texture* pausebut1;
static SDL_Texture* pausebut2;
static SDL_Texture* helpbut1;
static SDL_Texture* helpbut2;
static SDL_Texture* quitbut1;
static SDL_Texture* quitbut2;
static SDL_Texture* backbut1;
static SDL_Texture* backbut2;
static SDL_Texture* homebut1;
static SDL_Texture* homebut2;
static SDL_Texture* yesbut1;
static SDL_Texture* yesbut2;
static SDL_Texture* nobut1;
static SDL_Texture* nobut2;
static SDL_Texture* instruction;

static int reveal = 0;
static bool start = false;
static bool esc = false;
static bool help = false;

void initTitle()
{
	app.delegate.logic = logic;
	app.delegate.draw = draw;

	memset(app.keyboard, 0, sizeof(int) * MAX_KEYBOARD_KEYS);

    initMouse();
	logoTexture = loadTexture("gfx/warplane.png");
	startbut1 = loadTexture("gfx/play.png");
	startbut2 = loadTexture("gfx/colored_play.png");
	exitbut1 = loadTexture("gfx/exit.png");
    exitbut2 = loadTexture("gfx/colored_exit.png");
    contibut1 = loadTexture("gfx/continue.png");
    contibut2 = loadTexture("gfx/colored_continue.png");
    pausebut1 = loadTexture("gfx/pause.png");
    pausebut2 = loadTexture("gfx/colored_pause.png");
    helpbut1 = loadTexture("gfx/help.png");
    helpbut2 = loadTexture("gfx/colored_help.png");
    quitbut1 = loadTexture("gfx/quit.png");
    quitbut2 = loadTexture("gfx/colored_quit.png");
    backbut1 = loadTexture("gfx/back.png");
    backbut2  = loadTexture("gfx/colored_back.png");
    homebut1 = loadTexture("gfx/home.png");
    homebut2 = loadTexture("gfx/colored_home.png");
    yesbut1 = loadTexture("gfx/yes.png");
    yesbut2 = loadTexture("gfx/colored_yes.png");
    nobut1 = loadTexture("gfx/no.png");
    nobut2 = loadTexture("gfx/colored_no.png");
    instruction = loadTexture("gfx/instruction.png");
}
static bool InStartButton(){
    SDL_Rect r;
    SDL_QueryTexture(startbut1, NULL, NULL, &r.w, &r.h);
    return collision(app.mouse.x - MOUSE_HEIGHT/2,app.mouse.y - MOUSE_WIDTH/2,MOUSE_WIDTH,MOUSE_HEIGHT,(SCREEN_WIDTH / 2) - (r.w / 2), 450, r.w , r.h );
}
static bool InExitButton(){
    SDL_Rect r;
    SDL_QueryTexture(exitbut1, NULL, NULL, &r.w, &r.h);
    return collision(app.mouse.x - MOUSE_HEIGHT/2,app.mouse.y - MOUSE_WIDTH/2,MOUSE_WIDTH,MOUSE_HEIGHT,(SCREEN_WIDTH / 2) - (r.w / 2), 600, r.w , r.h );

}
static bool InHelpButton(){
    SDL_Rect r;
    SDL_QueryTexture(helpbut1, NULL, NULL, &r.w, &r.h);
    return collision(app.mouse.x - MOUSE_HEIGHT/2,app.mouse.y - MOUSE_WIDTH/2,MOUSE_WIDTH,MOUSE_HEIGHT,SCREEN_WIDTH - r.w - 10 , 10, r.w , r.h );
}
static void drawHelpButton(){
    SDL_Rect r;
    SDL_QueryTexture(helpbut1, NULL, NULL, &r.w, &r.h);
    if(InHelpButton()){
        blit(helpbut2,SCREEN_WIDTH - r.w - 10 , 10);
    }else blit(helpbut1,SCREEN_WIDTH - r.w - 10 , 10);
}

static void logic()
{
    doStarfield();

	if (reveal < SCREEN_HEIGHT)
	{
		reveal++;
	}

    doHelp();
    doBack();
    if(!help){
    doInputStart();

    if(InExitButton()){
        esc = true;
    }else esc = false;

    if (InExitButton() && app.mouse.button[SDL_BUTTON_LEFT])
	{
	    exit(1);
	}

    if(InStartButton()){
        start = true;
    }else start = false;

	if (InStartButton() && app.mouse.button[SDL_BUTTON_LEFT])
	{
		initStage();
	}}
}

static void draw()
{
	drawBackground();

	drawStarfield();

	drawLogo();

	if(help){
        drawHelpScreen();
	}

    drawMouse();
}
bool InHomeButton(){
    SDL_Rect r;
    SDL_QueryTexture(homebut1, NULL, NULL, &r.w, &r.h);
    return collision(app.mouse.x - MOUSE_HEIGHT/2,app.mouse.y - MOUSE_WIDTH/2,MOUSE_WIDTH,MOUSE_HEIGHT,SCREEN_WIDTH/2 - r.w/2 , SCREEN_HEIGHT/2 - r.h/2 - 180 , r.w , r.h );
}
void drawHome(){
    SDL_Rect r;
    SDL_QueryTexture(homebut1, NULL, NULL, &r.w, &r.h);
    if(InHomeButton()){
        blit(homebut2,SCREEN_WIDTH/2 - r.w/2 , SCREEN_HEIGHT/2 - r.h/2 - 180);
    }else blit(homebut1,SCREEN_WIDTH/2 - r.w/2 , SCREEN_HEIGHT/2 - r.h/2 - 180);
}

static bool InContinueButton(){
    SDL_Rect r;
    SDL_QueryTexture(contibut1, NULL, NULL, &r.w, &r.h);
    return collision(app.mouse.x - MOUSE_HEIGHT/2,app.mouse.y - MOUSE_WIDTH/2,MOUSE_WIDTH,MOUSE_HEIGHT,(SCREEN_WIDTH / 2) - (r.w / 2), SCREEN_HEIGHT/2 - (r.h)/2 - 50, r.w , r.h );
}
void drawContinue(){

    SDL_Rect r;
    SDL_QueryTexture(contibut1, NULL, NULL, &r.w, &r.h);
    if(InContinueButton()){
        blit(contibut2,(SCREEN_WIDTH / 2) - (r.w / 2), SCREEN_HEIGHT/2 - (r.h)/2 - 50);
    }else blit(contibut1,(SCREEN_WIDTH / 2) - (r.w / 2), SCREEN_HEIGHT/2 - (r.h)/2 - 50);
}
void doContinue(){
    if(InContinueButton() && app.mouse.button[SDL_BUTTON_LEFT]){
        app.pause = 0;
    }
}
static bool InBackButton(){
    SDL_Rect r;
    SDL_QueryTexture(backbut1, NULL, NULL, &r.w, &r.h);
    return collision(app.mouse.x - MOUSE_HEIGHT/2,app.mouse.y - MOUSE_WIDTH/2, MOUSE_WIDTH, MOUSE_HEIGHT,SCREEN_WIDTH - r.w - 10,SCREEN_HEIGHT - r.h - 10 ,  r.w , r.h );
}
static void drawBackButton(){
    SDL_Rect r;
    SDL_QueryTexture(backbut1, NULL, NULL, &r.w, &r.h);
    blit(backbut1,SCREEN_WIDTH - r.w - 10,SCREEN_HEIGHT - r.h - 10);
    if(InBackButton()){
        blit(backbut2,SCREEN_WIDTH - r.w - 10,SCREEN_HEIGHT - r.h - 10);
    }
}
void doHelp(){
    if(InHelpButton() && app.mouse.button[SDL_BUTTON_LEFT]){
        help = true;
    }
}
void doBack(){
    if(InBackButton() && app.mouse.button[SDL_BUTTON_LEFT]){
        help = false;
    }
}
void drawInstruction(){
    SDL_Rect r;
    SDL_QueryTexture(instruction, NULL, NULL, &r.w, &r.h);
    blit(instruction, SCREEN_WIDTH / 2 - r.w / 2, SCREEN_HEIGHT/2 - r.h/2);
}
void drawHelpScreen(){
    drawBackground();

	drawStarfield();

    drawBackButton();

    drawInstruction();
}

bool InQuitButton(){
    SDL_Rect r;
    SDL_QueryTexture(quitbut1, NULL, NULL, &r.w, &r.h);
    return collision(app.mouse.x - MOUSE_HEIGHT/2,app.mouse.y - MOUSE_WIDTH/2,MOUSE_WIDTH,MOUSE_HEIGHT,(SCREEN_WIDTH / 2) - (r.w / 2), SCREEN_HEIGHT/2 - (r.h)/2 + 100, r.w , r.h );
}
void drawQuit(){
    SDL_Rect r;
    SDL_QueryTexture(quitbut1, NULL, NULL, &r.w, &r.h);
    if(InQuitButton()){
        blit(quitbut2,(SCREEN_WIDTH / 2) - (r.w / 2), SCREEN_HEIGHT/2 - (r.h)/2 + 100);
    }else blit(quitbut1,(SCREEN_WIDTH / 2) - (r.w / 2), SCREEN_HEIGHT/2 - (r.h)/2 + 100);
}
void doQuit(){
    if(InQuitButton() && app.mouse.button[SDL_BUTTON_LEFT]){
        exit(1);
    }
}
bool InPauseButton(){
    SDL_Rect r;
    SDL_QueryTexture(pausebut1, NULL, NULL, &r.w, &r.h);
    return collision(app.mouse.x - MOUSE_HEIGHT/2,app.mouse.y - MOUSE_WIDTH/2,MOUSE_WIDTH,MOUSE_HEIGHT,SCREEN_WIDTH - r.w - 10 , 10, r.w , r.h );
}
void drawPause(){
    SDL_Rect r;
    SDL_QueryTexture(pausebut1, NULL, NULL, &r.w, &r.h);
    if(InPauseButton()){
        blit(pausebut2,SCREEN_WIDTH - r.w - 10, 10);
    }else blit(pausebut1,SCREEN_WIDTH - r.w - 10, 10);
}

bool InYesButton(){
    SDL_Rect r;
    SDL_QueryTexture(yesbut1, NULL, NULL, &r.w, &r.h);
    return collision(app.mouse.x - MOUSE_HEIGHT/2,app.mouse.y - MOUSE_WIDTH/2,MOUSE_WIDTH,MOUSE_HEIGHT,SCREEN_WIDTH/2 - 100 , 550, r.w , r.h );
}
void drawYes(){
    SDL_Rect r;
    SDL_QueryTexture(yesbut1, NULL, NULL, &r.w, &r.h);
    if(InYesButton()){
        blit(yesbut2,SCREEN_WIDTH/2 - 100 , 550 );
    }else blit(yesbut1,SCREEN_WIDTH/2 - 100 , 550);
}
bool InNoButton(){
    SDL_Rect r;
    SDL_QueryTexture(nobut1, NULL, NULL, &r.w, &r.h);
    return collision(app.mouse.x - MOUSE_HEIGHT/2,app.mouse.y - MOUSE_WIDTH/2,MOUSE_WIDTH,MOUSE_HEIGHT,SCREEN_WIDTH/2 + 70 , 550, r.w , r.h );
}
void drawNo(){
    SDL_Rect r;
    SDL_QueryTexture(nobut1, NULL, NULL, &r.w, &r.h);
    if(InNoButton()){
        blit(nobut2,SCREEN_WIDTH/2 + 70 , 550 );
    }else blit(nobut1,SCREEN_WIDTH/2 + 70 , 550);
}
void drawYesNo(){
    drawYes();
    drawNo();
}
void doYesNo(){
    if(InYesButton() && app.mouse.button[SDL_BUTTON_LEFT]){
        app.again = 1;
    }
    if(InNoButton() && app.mouse.button[SDL_BUTTON_LEFT]){
        exit(1);
    }
}
static void drawLogo()
{
	SDL_Rect r;

	r.x = 0;
	r.y = 0;

	SDL_QueryTexture(logoTexture, NULL, NULL, &r.w, &r.h);
	r.h = MIN(reveal, r.h);
	blitRect(logoTexture, &r, (SCREEN_WIDTH / 2) - (r.w / 2), 50);

	SDL_QueryTexture(startbut1, NULL, NULL, &r.w, &r.h);
	r.h = MIN(reveal, r.h);
	blitRect(startbut1, &r, (SCREEN_WIDTH / 2) - (r.w / 2), 450);
	if(start)blitRect(startbut2, &r, (SCREEN_WIDTH / 2) - (r.w / 2), 450);

	SDL_QueryTexture(exitbut1, NULL, NULL, &r.w, &r.h);
	r.h = MIN(reveal, r.h);
	blitRect(exitbut1, &r, (SCREEN_WIDTH / 2) - (r.w / 2), 600);
	if(esc)blitRect(exitbut2, &r, (SCREEN_WIDTH / 2) - (r.w / 2), 600);

	SDL_QueryTexture(helpbut1, NULL, NULL, &r.w, &r.h);
	r.h = MIN(reveal, r.h);
    blit(helpbut1,SCREEN_WIDTH - r.w - 10 , 10);
    if(InHelpButton()){
        blit(helpbut2,SCREEN_WIDTH - r.w - 10 , 10);
    }
}



