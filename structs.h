struct Explosion {
	float x;
	float y;
	float dx;
	float dy;
	int r, g, b, a;
	Explosion *next;
};
struct Mouse{
    int x, y;
    int button[MAX_MOUSE_BUTTON];
};
struct Debris {
	float x;
	float y;
	float dx;
	float dy;
	SDL_Rect rect;
	SDL_Texture *texture;
	int life;
	Debris *next;
};

typedef struct {
	int x;
	int y;
	int speed;
} Star;

typedef struct {
	void (*logic)();
	void (*draw)();
} Delegate;

typedef struct {
	SDL_Renderer *renderer;
	SDL_Window *window;

    Delegate delegate;
    Mouse mouse;
    bool pause = false;
    bool gameover = false;
    bool again = false;
    bool win = false;
    int keyboard[MAX_KEYBOARD_KEYS];
} App;
struct Entity {
	float x,y;
	int w,h;
	float dx,dy;
	int health;
	int reload;
    int side;
	SDL_Texture *texture;
	SDL_Texture *_texture;
	Entity *next;
};

typedef struct {
	Entity fighterHead, *fighterTail;
	Entity bulletHead, *bulletTail;
	Explosion explosionHead, *explosionTail;
	Debris debrisHead, *debrisTail;
	Entity pointsHead, *pointsTail;
	Entity meteoHead, *meteoTail;
	Entity heartHead, *heartTail;
	int score,defeat;
	int round;
} Stage;

