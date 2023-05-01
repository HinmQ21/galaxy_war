#include"common.h"
extern void blitRect(SDL_Texture *texture, SDL_Rect *src, int x, int y);
extern void blit(SDL_Texture *texture, int x, int y);
extern int collision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2);
extern void doStarfield();
extern void drawBackground();
extern void drawStarfield();
extern void initStarfield();
extern void initMouse();
extern void drawMouse();
extern void initStage();
extern void doInputStart();
extern SDL_Texture* loadTexture(char *filename);

extern App app;

