#include"sound.h"
static void loadSounds();

static Mix_Chunk* sounds[SND_MAX];
static Mix_Music* music;

void initSounds()
{
	memset(sounds, 0, sizeof(Mix_Chunk*) * SND_MAX);

	music = NULL;

	loadSounds();
}
static void loadSounds()
{
	sounds[SND_PLAYER_FIRE] = Mix_LoadWAV("sound/player_fire.ogg");
	sounds[SND_ALIEN_FIRE] = Mix_LoadWAV("sound/alien_fire.ogg");
	sounds[SND_PLAYER_DIE] = Mix_LoadWAV("sound/player_die.ogg");
	sounds[SND_ALIEN_DIE] = Mix_LoadWAV("sound/alien_die.ogg");
	sounds[SND_POINTS] = Mix_LoadWAV("sound/point.wav");
}
void loadMusic(char *filename)
{
	if (music != NULL)
	{
		Mix_HaltMusic();
		Mix_FreeMusic(music);
		music = NULL;
	}

	music = Mix_LoadMUS(filename);
}
void playMusic(int loop)
{
	Mix_PlayMusic(music, (loop) ? -1 : 0);
}
void playSound(int id, int channel)
{
	Mix_PlayChannel(channel, sounds[id], 0);
}
void initMusic(){
    loadMusic((char*)"music/jojo_cut.ogg");
    playMusic(1);
}

