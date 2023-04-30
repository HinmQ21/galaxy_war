#include "common.h"

extern void cleanup();
extern void doInput();
extern void drawGameOver();
extern void drawVictory();
extern void initAll();
extern void resetStage();
extern void prepareScene();
extern void drawMouse();
extern int gameoverTimer;
extern int victoryTimer;

extern void viewPauseStage();

App app;

Stage stage;
