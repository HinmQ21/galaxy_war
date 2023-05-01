#define SCREEN_WIDTH   1280
#define SCREEN_HEIGHT  720

#define MOUSE_WIDTH 50
#define MOUSE_HEIGHT 50

#define PLAYER_SPEED          3
#define PLAYER_BULLET_SPEED   10
#define ALIEN_BULLET_SPEED    8

#define MAX_KEYBOARD_KEYS 350
#define MAX_MOUSE_BUTTON 5

#define SIDE_PLAYER 0
#define SIDE_ALIEN  1
#define SIDE_BOSS 2
#define SIDE_METEO 3

#define BOSS_BAR_LEN 800
#define BOSS_MAX_HEALTH 40

#define FPS 60

#define MAX_STARS   500

#define PLAYER_HEALTH 2

#define MAX_SND_CHANNELS 8

#define MAX_LINE_LENGTH 1024

#define GLYPH_HEIGHT	30
#define GLYPH_WIDTH			18

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

enum
{
	CH_ANY = -1,
	CH_PLAYER,
	CH_ALIEN_FIRE,
	CH_POINTS
};

enum
{
	SND_PLAYER_FIRE,
	SND_ALIEN_FIRE,
	SND_PLAYER_DIE,
	SND_ALIEN_DIE,
	SND_POINTS,
	SND_MAX
};

