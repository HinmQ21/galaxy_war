#include "common.h"

extern void cleanup();
extern void doInput();
extern void doInputReset();
extern void initSDL();
extern void initGame();
extern void initGameOver();
extern void drawGameOver();
extern void drawBackground();
extern void initTitle();
extern void resetStage();
extern void prepareScene();
extern void presentScene();
extern void drawContinue();
extern void drawMouse();
extern void drawYesNo();
extern void doYesNo();
extern void doContinue();
extern void drawQuit();
extern void doQuit();
extern void drawText(int x, int y, int r, int g, int b,int align ,char* format, ...);

App app;

Stage stage;
