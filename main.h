#include "common.h"

extern void cleanup();
extern void doInput();
extern void drawGameOver();
extern void drawVictory();
extern void initAll();
extern void resetStage();
extern void prepareScene();
extern void drawContinue();
extern void drawMouse();
extern void doContinue();
extern int gameoverTimer;
extern int victoryTimer;
extern void drawQuit();
extern void doQuit();

App app;

Stage stage;
