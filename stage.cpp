#include"stage.h"

static SDL_Texture* background;
static SDL_Texture* allBackground[2];
static SDL_Texture* explosionTexture;
static SDL_Texture* heart;
static SDL_Texture* gameOverText;
static SDL_Texture* victoryText;
static SDL_Texture* play_againText;
static void logic();
static void draw();
static void initPlayer();
void resetStage();
static void doPlayer();
static void doFighters();
static void doEnemies();
static void doBullets();
static void doPoints();
static void doMeteorites();
static void doShield();
static void spawnShield();
void drawMouse();
void doStarfield();
static void drawFighters();
static void drawBullets();
static void addPoints(int x,int y);
void drawStarfield();
void drawBackground();
static void drawDebris();
static void fireBullet();
static void fireBossBullet(Entity *e);
static void spawnEnemies();
static void spawnBoss();
static void spawnMeteorite();
static bool bulletHitFighter(Entity *b);
static void fireAlienBullet(Entity *e);
static void clipPlayer();
void initStarfield();
void initBackGround();
static void doExplosions();
static void doDebris();
static void addExplosions(int x, int y, int num);
static void addDebris(Entity *e);
static void addBigDebris(Entity *e);
static void die(Entity* self);
static Entity *player;
static Entity *boss;
static SDL_Texture *bulletTexture ;
static SDL_Texture *enemyTexture1;
static SDL_Texture *enemyTexture2;
static SDL_Texture *shieldTexure;
static SDL_Texture *coverplayer;
static SDL_Texture *alienBulletTexture;
static SDL_Texture *alienBulletTexture2;
static SDL_Texture *pointsTexture;
static SDL_Texture *pointsTexture2;
static SDL_Texture *targetTexture;
static SDL_Texture *meteoriteTexture;
static SDL_Texture *meteorite_Texture;
static SDL_Texture *bossTexture;
static SDL_Texture *bossTexture2;
static SDL_Texture *bigExplosionTexture;
static SDL_Texture *bossBulletTexture1;
static SDL_Texture *bossBulletTexture2;
static SDL_Texture *bossBulletTexture3;
static SDL_Texture *bossBulletTexture4;
static SDL_Texture *bossBulletTexture5;
static SDL_Texture *specialBulletTexute;
static SDL_Texture *blackHoleTexture;
static int enemySpawnTimer;
static int meteoriteSpawnTimer;
static int bossSpawnTimes;
static int bossSpawnTimes2;
static int boss2Spawntimer;
static int heartSpawnTimer;
int gameoverTimer;
int victoryTimer;
static int nextRoundTimer;
static int highscore;
static Star stars[MAX_STARS];
static void doAiForEnemy();
static bool BossDefeated;
static bool InBlackHole;

void initStage()
{
	app.delegate.logic = logic;
	app.delegate.draw = draw;

	pointsTexture = loadTexture((char*)"gfx/points.png");
	pointsTexture2 = loadTexture((char*)"gfx/points2.png");
	heart = loadTexture((char*)"gfx/heart.png");
    alienBulletTexture = loadTexture((char*)"gfx/alienBullet.png");
    alienBulletTexture2 = loadTexture((char*)"gfx/alienBullet2.png");
	bulletTexture = loadTexture((char*)"gfx/playerBullet.png");
	enemyTexture1 = loadTexture((char*)"gfx/enemy.png");
	enemyTexture2 = loadTexture((char*)"gfx/enemy2.png");
	bossTexture = loadTexture((char*)"gfx/boss.png");
	bossTexture2 = loadTexture((char*)"gfx/boss2.png");
	explosionTexture = loadTexture((char*)"gfx/explosion.png");
	bigExplosionTexture = loadTexture((char*)"gfx/bigExplosion.png");
	bossBulletTexture1 = loadTexture((char*)"gfx/boss_bullet1.png");
	bossBulletTexture2 = loadTexture((char*)"gfx/boss_bullet2.png");
    bossBulletTexture3 = loadTexture((char*)"gfx/alienBigBullet.png");
    bossBulletTexture4 = loadTexture((char*)"gfx/alienBigBullet2.png");
    specialBulletTexute = loadTexture((char*)"gfx/special_bullet.png");
    bossBulletTexture5 = loadTexture((char*)"gfx/boss_bullet3.png");
	meteoriteTexture = loadTexture((char*)"gfx/meteorite.png");
	meteorite_Texture = loadTexture((char*)"gfx/meteo.png");
	shieldTexure = loadTexture((char*)"gfx/shieldpod.png");
	coverplayer = loadTexture((char*)"gfx/coverplayer.png");
	victoryText = loadTexture((char*)"gfx/victory.png");
	play_againText = loadTexture((char*)"gfx/play_again.png");
	blackHoleTexture = loadTexture((char*)"gfx/blackHole.png");
    resetStage();
}

void resetStage()
{
	Entity *e;
	Explosion *ex;
	Debris *d;

	while (stage.fighterHead.next)
	{
		e = stage.fighterHead.next;
		stage.fighterHead.next = e->next;
		free(e);
	}

	while (stage.bulletHead.next)
	{
		e = stage.bulletHead.next;
		stage.bulletHead.next = e->next;
		free(e);
	}
	while (stage.explosionHead.next)
	{
		ex = stage.explosionHead.next;
		stage.explosionHead.next = ex->next;
		free(ex);
	}

	while (stage.debrisHead.next)
	{
		d = stage.debrisHead.next;
		stage.debrisHead.next = d->next;
		free(d);
	}
    while (stage.pointsHead.next)
	{
		e = stage.pointsHead.next;
		stage.pointsHead.next = e->next;
		free(e);
	}
	while (stage.meteoHead.next)
    {
        e = stage.meteoHead.next;
        stage.meteoHead.next = e->next;
        free(e);
    }
    while(stage.heartHead.next){
        e = stage.heartHead.next;
        stage.heartHead.next = e->next;
        free(e);
    }
	memset(&stage, 0, sizeof(Stage));
	stage.fighterTail = &stage.fighterHead;
	stage.bulletTail = &stage.bulletHead;
    stage.explosionTail = &stage.explosionHead;
	stage.debrisTail = &stage.debrisHead;
    stage.pointsTail = &stage.pointsHead;
    stage.meteoTail = &stage.meteoHead;
    stage.heartTail = &stage.heartHead;

	initPlayer();
	initStarfield();

    bossSpawnTimes = 1;
    bossSpawnTimes2 = 1;
	enemySpawnTimer = 0;
	meteoriteSpawnTimer = 3*FPS;
    heartSpawnTimer = 10 * FPS;
	gameoverTimer = FPS * 2;
	victoryTimer = FPS * 2;
	nextRoundTimer = FPS * 5;
	BossDefeated = false;
	InBlackHole = false;

    stage.score = 0;
    stage.defeat = 0;
    stage.round = 1;

    app.again=0;
    app.gameover = 0;
    app.pause = false;

    background = allBackground[0];

    boss2Spawntimer = 10 * FPS;

    boss = NULL;

    app.win = false;
    app.gameover = false;

}

//Initialize texture of mouse
void initMouse(){
    targetTexture = loadTexture((char*)"gfx/target.png");
}

//Intialize coordinate of stars
void initStarfield()
{
	for (int i = 0 ; i < MAX_STARS ; i++)
	{
		stars[i].x = rand() % SCREEN_WIDTH;
		stars[i].y = rand() % SCREEN_HEIGHT;
		stars[i].speed = 1 + rand() % 8;
	}
}

//Intialize gameover texture
void initGameOver(){
    gameOverText = loadTexture("gfx/gameover.png");
}

//Draw gameover screen and do input
void drawGameOver(){
    drawBackground();
    SDL_Rect r;
    SDL_QueryTexture(gameOverText , NULL, NULL, &r.w, &r.h);
    blit(gameOverText,SCREEN_WIDTH/2 - r.w/2 , SCREEN_HEIGHT/2 - r.h/2);
    drawYesNo();
    drawMouse();
    doYesNo();
}

//Draw victory screen and do input
void drawVictory(){
    drawBackground();
    SDL_Rect r;
    SDL_QueryTexture(victoryText , NULL, NULL, &r.w, &r.h);
    blit(victoryText ,SCREEN_WIDTH/2 - r.w/2 + 25, SCREEN_HEIGHT/2 - r.h/2 - 50);

    SDL_QueryTexture(play_againText , NULL, NULL, &r.w, &r.h);
    blit(play_againText ,SCREEN_WIDTH/2 - r.w/2 + 25, 450);

    drawYesNo();
    drawMouse();
    doYesNo();
}

//Intialize background textures and set first background
void initBackGround(){
    allBackground[0] = loadTexture((char*)"gfx/background1.jpg");
    allBackground[1] = loadTexture((char*)"gfx/background2.jpg");

    background = allBackground[0];
}

//Intialize player
static void initPlayer()
{
    player = new Entity();
	memset(player, 0, sizeof(Entity));
	stage.fighterTail->next = player;
	stage.fighterTail = player;

	player->texture = loadTexture((char*)"gfx/player.png");
	player->_texture = loadTexture((char*)"gfx/player_onfire.png");

	SDL_QueryTexture(player->texture, NULL, NULL, &player->w, &player->h);
    player->x = 100;
	player->y = SCREEN_HEIGHT/2  - player->w;
	player->side = SIDE_PLAYER;
	player->health = PLAYER_HEALTH;
}

//Pause game
static void doPause(){
    if(InPauseButton() && app.mouse.button[SDL_BUTTON_LEFT]){
        app.pause = 1;
    }else app.pause = 0;
}
// Return to menu start
static void doHome(){
        if(InHomeButton() && app.mouse.button[SDL_BUTTON_LEFT]){
            initTitle();
            resetStage();
        }

}

// Do logic for player
static void doPlayer()
{
    if(player != NULL){
	player->dx = player->dy = 0;

	if (player->reload > 0)
	{
		player->reload--;
	}

	if (app.keyboard[SDL_SCANCODE_W])
	{
		player->dy = -PLAYER_SPEED;
	}

	if (app.keyboard[SDL_SCANCODE_S])
	{
		player->dy = PLAYER_SPEED;
	}

	if (app.keyboard[SDL_SCANCODE_A])
	{
		player->dx = -PLAYER_SPEED;
	}

	if (app.keyboard[SDL_SCANCODE_D])
	{
		player->dx = PLAYER_SPEED;
	}

	if (app.mouse.button[SDL_BUTTON_LEFT] && player->reload == 0)
	{
	    playSound(SND_PLAYER_FIRE, CH_PLAYER);
		fireBullet();
	}

	player->x += player->dx;
	player->y += player->dy;
    }
}

//Do logic for meteorites
static void doMeteorites(){
    Entity *m , *prev;
    prev = &stage.meteoHead;
    for(m = stage.meteoHead.next ; m!= NULL; m = m->next){
        if (player != NULL && collision(m->x,m->y,m->w,m->h,player->x,player->y,player->w,player->h)){
            m->health -- ;
            player->health --;
            playSound(SND_PLAYER_DIE,CH_ANY);
            addExplosions(m->x + m->w/2,m->y + m->h/2,32);
		}
		for(Entity *b = stage.bulletHead.next ; b != NULL; b = b->next){
            if(b->side == SIDE_PLAYER && collision(m->x, m->y, m->w, m->h, b->x, b->y, b->w, b->h)){
                m->health --;
                b->health --;
            playSound(SND_ALIEN_DIE,CH_ANY);
            addExplosions(m->x + m->w/2,m->y + m->h/2,32);
            }
		}
        m->x += m->dx;
        m->y += m->dy;
        if(m->y > SCREEN_HEIGHT + m->h || m->health <= 0){
            if(m->health <= 0)addDebris(m);
            if(m == stage.meteoTail){
                stage.meteoTail = prev;
            }
            prev->next = m->next;
            free(m);
            m = prev;
        }
        prev = m;
    }
}

// Do logic do heart icon
static void doHeart(){
    Entity *h, *prev;
    prev = &stage.heartHead;
    for(h = stage.heartHead.next; h != NULL; h = h->next){
            if (h->x < 0)
		{
			h->x = 0;
			h->dx = -h->dx;
		}

		if (h->x + h->w > SCREEN_WIDTH)
		{
			h->x = SCREEN_WIDTH - h->w;
			h->dx = -h->dx;
		}

		if (h->y < 0)
		{
			h->y = 0;
			h->dy = -h->dy;
		}

		if (h->y + h->h > SCREEN_HEIGHT)
		{
			h->y = SCREEN_HEIGHT - h->h;
			h->dy = -h->dy;
		}
		if(player != NULL && collision(h->x, h->y, h->w, h->h, player->x, player->y, player->w, player->h)){
            player->health++;
            h->health = 0;
            playSound(SND_POINTS,CH_POINTS);
		}
        h->x += h->dx;
        h->y += h->dy;
        if(--h->health <= 0)
        {
            if(h == stage.heartTail){
                stage.heartTail = prev;
            }
            prev->next = h->next;
            free(h);
            h = prev;
        }
        prev = h;
    }
}

// Intialize bullets for boss1
static void bossfireBullet(Entity *e){
    Entity *bullet;
    for(int i = 1; i <= 3; i++){
    bullet = new Entity();
	memset(bullet, 0, sizeof(Entity));
	stage.bulletTail->next = bullet;
	stage.bulletTail = bullet;
	bullet->x = e->x ;
	bullet->y = e->y + 100*i - 10;
	bullet->health = 3;
	bullet->side = SIDE_BOSS;
	bullet->dx = -ALIEN_BULLET_SPEED*2;
	bullet->texture = bossBulletTexture3;
	SDL_QueryTexture(bullet->texture, NULL, NULL, &bullet->w, &bullet->h);
    e->reload = FPS + ( rand() % FPS * 2 );
    }
}

//Intialize bullets for boss2
static void bossfireBullet2(Entity *e){
    Entity *bullet;
    for(int i = 1; i <= 3; i++){
    bullet = new Entity();
	memset(bullet, 0, sizeof(Entity));
	stage.bulletTail->next = bullet;
	stage.bulletTail = bullet;
	bullet->x = e->x ;
	bullet->y = e->y + 100*i - 55;
	bullet->health = 3;
	bullet->side = SIDE_BOSS;
	bullet->dx = -ALIEN_BULLET_SPEED*3;
	bullet->texture = bossBulletTexture4;
	SDL_QueryTexture(bullet->texture, NULL, NULL, &bullet->w, &bullet->h);
    e->reload = FPS + ( rand() % FPS * 2 );
    }
}

//Intialize special bullets for boss2
static void FireRainBullet(Entity *e){
    Entity *b;
    for(int i = 1; i <= 5; i++){
        b = new Entity ();
        memset(b, 0, sizeof(Entity));
        stage.bulletTail->next = b;
        stage.bulletTail = b;
        b->texture = specialBulletTexute;
        SDL_QueryTexture(b->texture, NULL, NULL, &b->w, &b->h);
        b->x = e->x;
        b->y = e->y + e->h/2;
        b->health = 2;
        b->side = SIDE_BOSS;
        e->reload = FPS + ( rand() % FPS * 2 );

        if(i==1)
        calcSlope( 0, 0,b->x, b->y,&b->dx, &b->dy);
        else if(i==2) calcSlope(0, SCREEN_HEIGHT / 4, b->x, b->y,&b->dx, &b->dy);
        else if(i==3)calcSlope(0, SCREEN_HEIGHT / 2,b->x, b->y,&b->dx, &b->dy);
        else if(i==4)calcSlope(0,3 * SCREEN_HEIGHT /4 ,b->x, b->y,&b->dx, &b->dy);
        else if(i==5)calcSlope(0, SCREEN_HEIGHT,b->x, b->y,&b->dx, &b->dy);

        b->dx *= ALIEN_BULLET_SPEED;
        b->dy *= ALIEN_BULLET_SPEED;
    }
}


// Do logic for enemies
static void doEnemies()
{
	Entity *e;

	for (e = stage.fighterHead.next ; e != NULL ; e = e->next)
	{
	    if (player != NULL &&e != player && collision(e->x,e->y,e->w,e->h,player->x,player->y,player->w,player->h)){
            e->health -- ;
            player->health --;

            playSound(SND_PLAYER_DIE,CH_ANY);
            addExplosions(player->x + player->w,player->y,32);
		}
		if (e->side != SIDE_PLAYER)
		{
			e->y = MIN(MAX(e->y, 0), SCREEN_HEIGHT - e->h);
			if (player != NULL && --e->reload <= 0)
			{
			    if(e->side == SIDE_ALIEN)
				fireAlienBullet(e);
				else {
                        if(rand()%2)
                        {
                            if(stage.round == 1) bossfireBullet(e);
                            else{
                                if(rand() % 2)
                                bossfireBullet2(e);
                            else FireRainBullet(e);
                            }
                        }
                else fireAlienBullet(e);
				}
				playSound(SND_ALIEN_FIRE, CH_ALIEN_FIRE);
			}
		}

	}
}

// Do logic for all planes
static void doFighters()
{
	Entity *e, *prev;

	prev = &stage.fighterHead;

	for (e = stage.fighterHead.next ; e != NULL ; e = e->next)
	{
		e->x += e->dx;
		e->y += e->dy;

		if(e->side == SIDE_BOSS) boss = e;

		if (e != player && e->x < -e->w)
		{
			e->health = 0 ;
		}
        if(e->side == SIDE_BOSS){
            if(e->x <= SCREEN_WIDTH - e->w){
                e->dx = 0;
            }
        }


		if (e->health <= 0)
		{
		    addExplosions(e->x,e->y,32);
            addDebris(e);
			if (e == player)
			{
				player = NULL;
			}
			if(e->side == SIDE_BOSS){
                if(stage.round == 2)app.win = true;
                boss = NULL;
                addBigDebris(e);
                die(e);
                BossDefeated = true;
                stage.score += 100;
                highscore = MAX(highscore, stage.score);
			}

			if (e == stage.fighterTail)
			{
				stage.fighterTail = prev;
			}

			prev->next = e->next;
			free(e);
			e = prev;
		}

		prev = e;
	}
}

// Do logic for stars
void doStarfield()
{
	for (int i = 0 ; i < MAX_STARS ; i++)
	{
		stars[i].x -= stars[i].speed;
		if (stars[i].x < 0)
		{
			stars[i].x = SCREEN_WIDTH;
		}
	}
}

// Do logic for explosions
static void doExplosions()
{
	Explosion *e, *prev;

	prev = &stage.explosionHead;

	for (e = stage.explosionHead.next ; e != NULL ; e = e->next)
	{
		e->x += e->dx;
		e->y += e->dy;

		if (--e->a <= 0)
		{
			if (e == stage.explosionTail)
			{
				stage.explosionTail = prev;
			}

			prev->next = e->next;
			free(e);
			e = prev;
		}

		prev = e;
	}
}

// Do logic for debrises
static void doDebris()
{
	Debris *d, *prev;

	prev = &stage.debrisHead;

	for (d = stage.debrisHead.next ; d != NULL ; d = d->next)
	{
		d->x += d->dx;
		d->y += d->dy;

		d->dy += 1;

		if (--d->life == 0)
		{
			if (d == stage.debrisTail)
			{
				stage.debrisTail = prev;
			}

			prev->next = d->next;
			free(d);
			d = prev;
		}

		prev = d;
	}
}

// Do logic for point icons
static void doPoints()
{
	Entity *e, *prev;

	prev = &stage.pointsHead;

	for (e = stage.pointsHead.next ; e != NULL ; e = e->next)
	{
		if (e->x < 0)
		{
			e->x = 0;
			e->dx = -e->dx;
		}

		if (e->x + e->w > SCREEN_WIDTH)
		{
			e->x = SCREEN_WIDTH - e->w;
			e->dx = -e->dx;
		}

		if (e->y < 0)
		{
			e->y = 0;
			e->dy = -e->dy;
		}

		if (e->y + e->h > SCREEN_HEIGHT)
		{
			e->y = SCREEN_HEIGHT - e->h;
			e->dy = -e->dy;
		}

		e->x += e->dx;
		e->y += e->dy;

		if (player != NULL && collision(e->x, e->y, e->w, e->h, player->x, player->y, player->w, player->h))
		{
			e->health = 0;

            if(stage.round == 1)
			stage.score++;
            else stage.score += 2;
			highscore = MAX(stage.score, highscore);

			playSound(SND_POINTS, CH_POINTS);
		}

		if (--e->health <= 0)
		{
			if (e == stage.pointsTail)
			{
				stage.pointsTail = prev;
			}

			prev->next = e->next;
			free(e);
			e = prev;
		}

		prev = e;
	}
}

// Intialize explosions
static void addExplosions(int x, int y, int num)
{
	Explosion *e;

	for (int i = 0 ; i < num ; i++)
	{
        e = new Explosion();
		memset(e, 0, sizeof(Explosion));
		stage.explosionTail->next = e;
		stage.explosionTail = e;

		e->x = x + (rand() % 32) - (rand() % 32);
		e->y = y + (rand() % 32) - (rand() % 32);
		e->dx = (rand() % 10) - (rand() % 10);
		e->dy = (rand() % 10) - (rand() % 10);

		e->dx /= 10;
		e->dy /= 10;

		switch (rand() % 4)
		{
			case 0:
				e->r = 255; //Red
				break;

			case 1:
				e->r = 255;  //Orange
				e->g = 128;
				break;
            case 2:
                e->r = 255;   // yellow
                e->g = 255;
                break;
			default:
				e->r = 255;    //white
				e->g = 255;
				e->b = 255;
				break;
		}

		e->a = rand() % FPS * 3;
	}
}

// Intialize debrises
static void addDebris(Entity *e)
{
	Debris *d;
	int x, y, w, h;

	w = e->w / 2;
	h = e->h / 2;

	for (y = 0 ; y <= h ; y += h)
	{
		for (x = 0 ; x <= w ; x += w)
		{
            d = new Debris ();
			memset(d, 0, sizeof(Debris));
			stage.debrisTail->next = d;
			stage.debrisTail = d;

			d->x = e->x + e->w / 2;
			d->y = e->y + e->h / 2;
            d->dx = -5 + rand() % 11;
			d->dy = -(5 + (rand() % 12));
			d->life = FPS ;

			if(e==player || e->side == SIDE_METEO){
                d->texture = e->_texture;
			}else d->texture = e->texture;

			d->rect.x = x;
			d->rect.y = y;
			d->rect.w = w;
			d->rect.h = h;
		}
	}
}

static void addBigDebris(Entity *e)
{
	Debris *d;
	int x, y, w, h;

	w = e->w / 3;
	h = e->h / 3;

	for (y = 0 ; y <= 2*h ; y += h)
	{
		for (x = 0 ; x <= 2*w ; x += w)
		{
            d = new Debris();
			memset(d, 0, sizeof(Debris));
			stage.debrisTail->next = d;
			stage.debrisTail = d;

			d->x = e->x + e->w / 2;
			d->y = e->y + e->h / 2;
            d->dx = -5 + rand() % 11;
			d->dy = -(5 + (rand() % 12));
			d->life = FPS ;
			d->texture = e->texture;

			d->rect.x = x;
			d->rect.y = y;
			d->rect.w = w;
			d->rect.h = h;
		}
	}
}

// Intialize point icons
static void addPoints(int x, int y)
{
	Entity *e;

    e = new Entity();
	memset(e, 0, sizeof(Entity));
	stage.pointsTail->next = e;
	stage.pointsTail = e;

	e->x = x;
	e->y = y;
	e->dx = -(rand() % 5);
	e->dy = (rand() % 5) - (rand() % 5);
	e->health = FPS * 5;
	if(stage.round == 1)
	e->texture = pointsTexture;
    else e->texture = pointsTexture2;
	SDL_QueryTexture(e->texture, NULL, NULL, &e->w, &e->h);

	e->x -= e->w / 2;
	e->y -= e->h / 2;
}

// Intialize player bullet
static void fireBullet()
{
	Entity *bullet;

    bullet = new Entity();
	memset(bullet, 0, sizeof(Entity));
	stage.bulletTail->next = bullet;
	stage.bulletTail = bullet;

	bullet->x = player->x;
	bullet->y = player->y;

	calcSlope(app.mouse.x , app.mouse.y - 25 , bullet->x, bullet->y, &bullet->dx, &bullet->dy);

	bullet->dx *= PLAYER_BULLET_SPEED;
	bullet->dy *= PLAYER_BULLET_SPEED;

	bullet->health = 1;
	bullet->texture = bulletTexture;
    bullet->side = SIDE_PLAYER;
	SDL_QueryTexture(bullet->texture, NULL, NULL, &bullet->w, &bullet->h);

	bullet->y += (player->h / 2) - (bullet->h / 2);
	bullet->x += player->w/2;

	player->reload = 16;
}

// Intialize enemy bullets
static void fireAlienBullet(Entity *e)
{
	Entity *bullet;

    bullet = new Entity();
	memset(bullet, 0, sizeof(Entity));
	stage.bulletTail->next = bullet;
	stage.bulletTail = bullet;

	bullet->x = e->x;
	bullet->y = e->y;

	if(e->side == SIDE_ALIEN){
        if(stage.round == 1){
	bullet->texture = alienBulletTexture;
    bullet->health = 1;
        }
    else {
            bullet->texture = alienBulletTexture2;
            bullet->health = 2;
    }

        bullet->side = SIDE_ALIEN;
	}
	else {
            int r = rand() % 3;

            switch(r){
            case 0 :
            bullet->texture = bossBulletTexture1;
            break;
            case 1 :
            bullet->texture = bossBulletTexture2;
            break;
            case 2 :
            bullet->texture = bossBulletTexture5;
            }

            bullet->side = SIDE_BOSS;
            bullet->health = 3;
	}

	SDL_QueryTexture(bullet->texture, NULL, NULL, &bullet->w, &bullet->h);

	bullet->y += (e->h / 2) - (bullet->h / 2);

	calcSlope(player->x + (player->w / 2), player->y + (player->h / 2), bullet->x, bullet->y, &bullet->dx, &bullet->dy);

	bullet->dx *= ALIEN_BULLET_SPEED;
	bullet->dy *= ALIEN_BULLET_SPEED;

	e->reload = FPS + ( rand() % FPS * 2 );
}

// Entity die
static void die(Entity *self)
{
	int i, x, y;
    SDL_Rect rect;
    SDL_QueryTexture(self->texture, NULL, NULL, &rect.w, &rect.h);

	for (i = 0 ; i < 25 ; i++)
	{
		x = self->x + (rect.w / 2);
		x -= rand() % rect.w;
		x += rand() % rect.w;

		y = self->y + (rect.h / 2);
		y -= rand() % rect.h;
		y += rand() % rect.h;
        addExplosions(x,y,16);
	}
}

// Do logic for all bullets
static void doBullets()
{
	Entity *b, *prev;

	prev = &stage.bulletHead;

	for (b = stage.bulletHead.next ; b != NULL ; b = b->next)
	{
		b->x += b->dx;
		b->y += b->dy;
        for(Entity* bu = stage.bulletHead.next; bu != NULL ; bu = bu->next){
            if(bu->side != b->side && collision(b->x,b->y,b->w,b->h , bu->x, bu->y, bu->w, bu->h)){
                bu->health --;
                b->health --;
                addExplosions(bu->x,bu->y,10);
            }
        }
		if ( bulletHitFighter(b) || b->x < -b->w || b->y < -b->h || b->x > SCREEN_WIDTH || b->y > SCREEN_HEIGHT || b->health == 0)
		{
			if (b == stage.bulletTail)
			{
				stage.bulletTail = prev;
			}

			prev->next = b->next;
			free(b);
			b = prev;
		}

		prev = b;
	}
}

// Check collisions between planes and bullets
static bool bulletHitFighter(Entity *b)
{
	Entity *e;

	for (e = stage.fighterHead.next ; e != NULL ; e = e->next)
	{
    if (e->side != b->side && collision(b->x, b->y, b->w, b->h, e->x, e->y, e->w, e->h))
    {
        if(e->side != SIDE_BOSS)
        addExplosions(b->x,b->y,32);
        else addExplosions(b->x, b->y, 8);
        b->health-- ;
        e->health-- ;
        if (e == player)
	{
		playSound(SND_PLAYER_DIE, CH_PLAYER);
	}
	else
	{

	    if(e->side == SIDE_ALIEN && e->health <= 0){
	        stage.defeat ++;
            addPoints(e->x + e->w / 2, e->y + e->h / 2);
	    }
		playSound(SND_ALIEN_DIE, CH_ANY);
	}


        return true;
    }
	}

	return false;
}

// Intialize enemies
static void spawnEnemies()
{
	Entity *enemy;

	if (--enemySpawnTimer <= 0)
	{
        enemy = new Entity();
		memset(enemy, 0, sizeof(Entity));
		stage.fighterTail->next = enemy;
		stage.fighterTail = enemy;

		enemy->x = SCREEN_WIDTH;
		enemy->y = rand() % SCREEN_HEIGHT;
		if(stage.round == 1){
            enemy->health = 1;
            enemy->texture = enemyTexture1;
		}
		else {
                enemy->texture = enemyTexture2;
                enemy->health = 2;
		}

		SDL_QueryTexture(enemy->texture, NULL, NULL, &enemy->w, &enemy->h);

		enemy->dx = -(2 + (rand() % 2));
        enemy->dy = (-100 + rand() % 201);
        enemy->dy /= 100;

		enemySpawnTimer = 30 + (rand() % 60);
		enemy->side = SIDE_ALIEN;
		enemy->reload = FPS * (1 + (rand() % 3));
	}
}

// Intialize heart icons
static spawnHeart(){
    Entity *h;
    if(--heartSpawnTimer <= 0){
        h = new Entity();
        memset(h, 0, sizeof(Entity));
        stage.heartTail->next = h;
        stage.heartTail = h;

        h->x = SCREEN_WIDTH;
        h->y = rand() % SCREEN_HEIGHT;
        h->dx = -4;
        h->dy = -5 + rand() % 11;
        h->texture = heart;
        SDL_QueryTexture(heart, NULL, NULL, &h->w, &h->h);
        h->health = 5 * FPS;
        heartSpawnTimer = 10 * FPS;
    }
}

// Intialize boss1
static void spawnBoss(){
    if(bossSpawnTimes-- > 0)
    {
    Entity *boss;
    boss = new Entity();
    memset(boss, 0, sizeof(Entity));
    stage.fighterTail->next = boss;
    stage.fighterTail = boss;

    boss->texture = bossTexture;
    SDL_QueryTexture(boss->texture, NULL, NULL, &boss->w, &boss->h);
    boss->x = SCREEN_WIDTH;
    boss->y = SCREEN_HEIGHT / 2 - boss->h/2;
    boss->dx = -1;
    boss->side = SIDE_BOSS;
    boss->health = BOSS_MAX_HEALTH;
    boss->reload = FPS * (1 + (rand() % 3));
    }
}

// Intialize boss2
static void spawnBoss2(){
    if(bossSpawnTimes2-- > 0)
    {
        Entity *boss;
        boss = new Entity();
        memset(boss, 0, sizeof(Entity));
        stage.fighterTail->next = boss;
        stage.fighterTail = boss;

        boss->texture = bossTexture2;
        SDL_QueryTexture(boss->texture, NULL, NULL, &boss->w, &boss->h);
        boss->x = SCREEN_WIDTH;
        boss->y = SCREEN_HEIGHT / 2 - boss->h/2;
        boss->dx = -1;
        boss->side = SIDE_BOSS;
        boss->health = BOSS_MAX_HEALTH * 2;
        boss->reload = FPS * (1 + (rand() % 2));
    }
}

// Intialize meteorites
static void spawnMeteorite(){
    Entity *meteo;
    if(--meteoriteSpawnTimer < 0){
        meteo = new Entity();
        memset(meteo, 0, sizeof(Entity));
        stage.meteoTail->next = meteo;
        stage.meteoTail = meteo;

        meteo->texture = meteoriteTexture;
        meteo->_texture = meteorite_Texture;
        SDL_QueryTexture(meteo->texture, NULL, NULL, &meteo->w, &meteo->h);
        meteo->x = rand() % SCREEN_WIDTH;
        meteo->y = -meteo->h;
        meteo->dx = -3;
        meteo->dy = 4;
        meteo->side = SIDE_METEO;
        meteo->health = 2;
        meteoriteSpawnTimer = 3*FPS + rand()% (3*FPS);
    }
}

// Don't let player to be able to run off-screen
static void clipPlayer()
{
	if (player != NULL)
	{
		if (player->x < 0)
		{
			player->x = 0;
		}

		if (player->y < 0)
		{
			player->y = 0;
		}

		if (player->x > SCREEN_WIDTH - player->w)
		{
			player->x = SCREEN_WIDTH - player->w;
		}

		if (player->y > SCREEN_HEIGHT - player->h)
		{
			player->y = SCREEN_HEIGHT - player->h;
		}
	}
}

// Present background
void drawBackground()
{
	SDL_Rect dest;
    dest.x = 0;
    dest.y = 0;
    dest.w = SCREEN_WIDTH;
    dest.h = SCREEN_HEIGHT;
    SDL_RenderCopy(app.renderer,background,NULL,&dest);

}

// Present meteorites
void drawMeteorite(){
    for(Entity* m = stage.meteoHead.next; m != NULL ; m = m->next){
        blit(m->texture, m->x, m->y);
    }
}

// Present point icons
static void drawPoints()
{
	Entity* e;

	for (e = stage.pointsHead.next; e != NULL; e = e->next)
	{
		if (e->health > (FPS *2) || e->health % 12 < 6)
		{
			blit(e->texture, e->x, e->y);
		}
	}
}

// Present stars
void drawStarfield()
{
	int i, c;

	for (i = 0 ; i < MAX_STARS ; i++)
	{
		c = 32 * stars[i].speed;

		SDL_SetRenderDrawColor(app.renderer, c, c, c, 255);

		SDL_RenderDrawLine(app.renderer, stars[i].x, stars[i].y, stars[i].x + 3, stars[i].y);
	}
}

// Present debrises
static void drawDebris()
{
	Debris *d;

	for (d = stage.debrisHead.next ; d != NULL ; d = d->next)
	{
		blitRect(d->texture, &d->rect, d->x, d->y);
	}
}

// Present explosions
static void drawExplosions()
{
	Explosion *e;

	SDL_SetRenderDrawBlendMode(app.renderer, SDL_BLENDMODE_ADD);
	SDL_SetTextureBlendMode(explosionTexture, SDL_BLENDMODE_ADD);

	for (e = stage.explosionHead.next ; e != NULL ; e = e->next)
	{
		SDL_SetTextureColorMod(explosionTexture, e->r, e->g, e->b);
        SDL_SetTextureAlphaMod(explosionTexture, e->a);

		blit(explosionTexture, e->x, e->y);
	}

    SDL_SetRenderDrawBlendMode(app.renderer, SDL_BLENDMODE_NONE);
}

// Present all planes
static void drawFighters()
{
	Entity *e;

	for (e = stage.fighterHead.next ; e != NULL ; e = e->next)
	{
	    if(e == player && e->health < PLAYER_HEALTH){
            blit(e->_texture,e->x,e->y);
	    }else{
	    blit(e->texture, e->x, e->y);
	    }

    }
}

// Present all bullets
static void drawBullets()
{
	Entity *b;

	for (b = stage.bulletHead.next ; b != NULL ; b = b->next)
	{
	    if(b->health != 0)
		blit(b->texture, b->x, b->y);
	}
}

// Present head up display
static void drawHud()
{
	drawText(10, 10, 255, 255, 255 ,"SCORE: %03d", stage.score);
    drawText(10, 50, 255, 0 ,0 ,"DEFEAT: %03d", stage.defeat);
	if (stage.score > 0 && stage.score == highscore)
	{
		drawText(900, 10, 0, 255, 0 ,"HIGH SCORE: %03d", highscore);
	}
	else
	{
		drawText(900, 10, 255, 255, 255 ,"HIGH SCORE: %03d", highscore);
	}
}

// Present life of player
static void drawLives(){
    SDL_Rect rect;

    SDL_QueryTexture(heart,NULL,NULL,&rect.w,&rect.h);
    if(player != NULL){
    blit(heart,SCREEN_WIDTH/2-rect.w,0);
    drawText(SCREEN_WIDTH/2 + rect.w / 2,10, 255, 0, 0, "X %d", player->health);
    }

}

// Present heart icon
static void drawHeart(){
    Entity *h;

    for( h = stage.heartHead.next ; h != NULL; h = h->next){
        if(h->health > (FPS * 2) || h->health % 12 < 6){
            blit(h->texture, h->x, h->y);
        }
    }
}

// Present life of bosses
static void drawBossBar(){
    if(boss != NULL)
    {
    drawText(100, SCREEN_HEIGHT - GLYPH_HEIGHT , 255, 255, 255, "BOSS:");

    SDL_Rect r;
    r.h = 20;
    if(stage.round == 1)
    r.w = BOSS_BAR_LEN -(-boss->health + BOSS_MAX_HEALTH)*(BOSS_BAR_LEN/BOSS_MAX_HEALTH);
    else     r.w = BOSS_BAR_LEN -(-boss->health + 2*BOSS_MAX_HEALTH)*(BOSS_BAR_LEN/(2*BOSS_MAX_HEALTH));
    r.x = 200;
    r.y = SCREEN_HEIGHT - 20;
    SDL_SetRenderDrawColor(app.renderer,255, 0, 0, 0);
    SDL_RenderFillRect(app.renderer, &r);

    SDL_SetRenderDrawColor(app.renderer, 255,255,255,0);
    SDL_RenderDrawRect(app.renderer, &r);
    }
}

// Present mouse
void drawMouse(){
    SDL_GetMouseState(&app.mouse.x, &app.mouse.y);
	blitM(targetTexture,app.mouse.x,app.mouse.y,1);
}

// Present blackhole
void drawBlackHole(){
        SDL_Rect rect;

    SDL_QueryTexture(blackHoleTexture, NULL, NULL, &rect.w, &rect.h);

    blit(blackHoleTexture, SCREEN_WIDTH - rect.w, SCREEN_HEIGHT / 2 - rect.h/2);
}

// Do logic for blackhole
void doBlackHole(){
    SDL_Rect rect;

    SDL_QueryTexture(blackHoleTexture, NULL, NULL, &rect.w, &rect.h);

    if( player != NULL && collision(player->x, player->y, player->w, player->h, SCREEN_WIDTH - 3*rect.w / 4, SCREEN_HEIGHT / 2 - rect.h/4, rect.w/2,rect.h/2)){
        InBlackHole = true;
        player->x = 100;
        player->y = SCREEN_HEIGHT/2  - player->w;
        stage.round = 2;
    }
}

// Draw pause screen and do input
void viewPauseStage(){
    drawContinue();
    drawQuit();
    drawHome();
    doQuit();
    doContinue();
    doHome();
    drawMouse();
}

// All logic of game
static void logic()
{
    doPause();
    doStarfield();
	doPlayer();
	doEnemies();
	doFighters();
	doBullets();
	doExplosions();
	doDebris();
	doPoints();
	spawnMeteorite();
	doMeteorites();

    if(BossDefeated && --nextRoundTimer < 0) doBlackHole();
    spawnHeart();
    doHeart();
	if(stage.defeat < 20)
	{
	    spawnEnemies();
	}else{
	    if(bossSpawnTimes > 0)
	    {
        spawnBoss();
	    }

        if(BossDefeated && InBlackHole){
                background = allBackground[1];
                if(--boss2Spawntimer > 0)
                spawnEnemies();
                else {
                        spawnBoss2();
                        spawnEnemies();
                }
        }

	}
	clipPlayer();

	if(player == NULL ){
        app.gameover = 1;
	}
}

// All draw of game
static void draw()
{
    drawBackground();

	drawStarfield();

	drawBossBar();

	drawPoints();

    drawFighters();

	drawBullets();

	drawDebris();

	drawExplosions();

	if(BossDefeated && nextRoundTimer < 0 && !InBlackHole) drawBlackHole();

	drawMeteorite();

    drawHeart();

	drawHud();

	drawLives();

	drawPause();

	drawMouse();

}
