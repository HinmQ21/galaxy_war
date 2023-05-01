#include"common.h"

extern void blit(SDL_Texture *texture, int x, int y);
extern void blitRect(SDL_Texture *texture,SDL_Rect *scr,int x,int y);
extern void blitM(SDL_Texture *texture, int x, int y, int center);
extern SDL_Texture *loadTexture(char *filename);
extern int collision(int x1,int y1, int w1, int h1, int x2, int y2, int w2, int h2);
extern int calcSlope(int x1,int y1, int x2, int y2, float *dx, float *dy);
extern void playSound(int id, int channel);
extern void drawText(int x, int y, int r, int g, int b, char* format, ...);
extern void drawPause();
extern void drawHome();
extern void drawYesNo();
extern void doYesNo();
extern void initTitle();
extern bool InPauseButton();
extern bool InHomeButton();
extern void doMusic();
extern void drawQuit();
extern void doQuit();
extern void drawContinue();
extern void doContinue();


extern App app;
extern Stage stage;
