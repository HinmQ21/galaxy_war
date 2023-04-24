#include"init.h"
void initSDL() {
    int rendererFlags, windowFlags;

    rendererFlags = SDL_RENDERER_ACCELERATED;

    windowFlags = 0;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "Couldn't initialize SDL: " << SDL_GetError() << std::endl;
        exit(1);
    }

    app.window = SDL_CreateWindow("Galaxy War", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                  SCREEN_WIDTH, SCREEN_HEIGHT, windowFlags);

    app.renderer = SDL_CreateRenderer(app.window, -1, rendererFlags);

    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) < 0)
	{
		std::cout << "Couldn't initialize SDL Mixer\n";
		exit(1);
	}
    SDL_ShowCursor(0);
	Mix_AllocateChannels(MAX_SND_CHANNELS);
}
void initGame(){
    initBackGround();
    initFonts();
    initGameOver();
    initStarfield();
    initSounds();
    initMusic();
}
void initAll(){
    initSDL();

	initGame();

    initTitle();
}
void cleanup() {
    SDL_DestroyRenderer(app.renderer);

    SDL_DestroyWindow(app.window);

    SDL_Quit();
}
