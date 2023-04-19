#include"stage.h"

static SDL_Texture* background;
static SDL_Texture* explosionTexture;
static SDL_Texture* heart;
static SDL_Texture* gameOverText;
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
static Entity *player;
static Entity *boss;
static SDL_Texture *bulletTexture ;
static SDL_Texture *enemyTexture;
static SDL_Texture *alienBulletTexture;
static SDL_Texture *pointsTexture;
static SDL_Texture *targetTexture;
static SDL_Texture *meteoriteTexture;
static SDL_Texture *bossTexture;
static SDL_Texture *bigExplosionTexture;
static SDL_Texture *bossBulletTexture1;
static SDL_Texture *bossBulletTexture2;
static int enemySpawnTimer;
static int meteoriteSpawnTimer;
static int bossSpawnTimes;
static int stageResetTimer;
static int highscore;
static Star stars[MAX_STARS];
static void doAiForEnemy();
static bool BossAppear;

void initStage()
{
	app.delegate.logic = logic;
	app.delegate.draw = draw;

    stage.explosionTail = &stage.explosionHead;
	stage.debrisTail = &stage.debrisHead;
	pointsTexture = loadTexture("gfx/points.png");
	heart = loadTexture((char*)"gfx/heart.png");
    alienBulletTexture = loadTexture((char*)"gfx/alienBullet.png");
	bulletTexture = loadTexture((char*)"gfx/playerBullet.png");
	enemyTexture = loadTexture((char*)"gfx/enemy.png");
	bossTexture = loadTexture((char*)"gfx/boss.png");
	explosionTexture = loadTexture((char*)"gfx/explosion.png");
	bigExplosionTexture = loadTexture((char*)"gfx/bigExplosion.png");
	bossBulletTexture1 = loadTexture((char*)"gfx/boss_bullet1.png");
	bossBulletTexture2 = loadTexture((char*)"gfx/boss_bullet2.png");
	meteoriteTexture = loadTexture((char*)"gfx/meteorite.png");
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
	memset(&stage, 0, sizeof(Stage));
	stage.fighterTail = &stage.fighterHead;
	stage.bulletTail = &stage.bulletHead;
    stage.explosionTail = &stage.explosionHead;
	stage.debrisTail = &stage.debrisHead;
    stage.pointsTail = &stage.pointsHead;
    stage.meteoTail = &stage.meteoHead;
	initPlayer();
	initStarfield();

    bossSpawnTimes = 1;
	enemySpawnTimer = 0;
	meteoriteSpawnTimer = 3*FPS;
	BossAppear = false;

    stage.score = 0;
    stage.defeat = 0;
    app.win = false;

	stageResetTimer = FPS * 3;
}
void initMouse(){
    targetTexture = loadTexture((char*)"gfx/target.png");
}
void initStarfield()
{
	for (int i = 0 ; i < MAX_STARS ; i++)
	{
		stars[i].x = rand() % SCREEN_WIDTH;
		stars[i].y = rand() % SCREEN_HEIGHT;
		stars[i].speed = 1 + rand() % 8;
	}
}
void initGameOver(){
    gameOverText = loadTexture("gfx/gameover.png");
}
void drawGameOver(){
    SDL_Rect r;
    SDL_QueryTexture(gameOverText , NULL, NULL, &r.w, &r.h);
    blit(gameOverText,SCREEN_WIDTH/2 - r.w/2 , SCREEN_HEIGHT/2 - r.h/2);
}
void initBackGround(){
    background = loadTexture((char*)"gfx/background.jpg");
}
static void initPlayer()
{
	player =(Entity*) malloc(sizeof(Entity));
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
static void doPause(){
    if(app.start)
    if(InPauseButton() && app.mouse.button[SDL_BUTTON_LEFT]){
        app.pause = 1;
    }else app.pause = 0;
}
static void doHome(){
    if(app.start){
        if(InHomeButton() && app.mouse.button[SDL_BUTTON_LEFT]){
            initTitle();
        }
    }
}
static void logic()
{
    doPause();
    doHome();
    doStarfield();
	doPlayer();
	doEnemies();
	//doAiForEnemy();
	doFighters();
	doBullets();
	doExplosions();
	doDebris();
	doPoints();
	spawnMeteorite();
	doMeteorites();
	if(stage.defeat < 5)
	{
	    spawnEnemies();
	}else{
	    BossAppear = true;
        spawnBoss();
	}
	clipPlayer();

	if(player == NULL  && --stageResetTimer <= 0){
        app.gameover = 1;
	}
}

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
            addBigDebris(m);
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
				fireAlienBullet(e);
				playSound(SND_ALIEN_FIRE, CH_ALIEN_FIRE);
			}
		}

	}
}
static void doAiForEnemy(){
    for(Entity *e = stage.fighterHead.next; e != NULL ;e = e->next){
        if(e->side == SIDE_ALIEN){
            for(Entity *b = stage.bulletHead.next; b != NULL ;b = b->next){
                if(b->side == SIDE_PLAYER && b->y > e->y && b->y + b->h < e->y + e->h && e->x - b->x <= 600){
                    e->y += 5;
                }
            }
        }
    }
}

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
                //e->dy = -2 + rand()%5;
            }
            if(e->health <= 0) {
                    addBigDebris(e);
                    stage.score += 100;
                    highscore = MAX(highscore, stage.score);
                    app.win = 1;
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

			stage.score++;

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
static void addExplosions(int x, int y, int num)
{
	Explosion *e;

	for (int i = 0 ; i < num ; i++)
	{
		e = (Explosion*)malloc(sizeof(Explosion));
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

//			case 2:
//				e->b = 255;  // cyan
//				e->g = 255;
//				break;
            case 2:
                e->r = 255;   // yellow
                e->g = 255;
                break;
//            case 4 :
//                e->g = 128;  //green

			default:
				e->r = 255;    //white
				e->g = 255;
				e->b = 255;
				break;
		}

		e->a = rand() % FPS * 3;
	}
}

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
			d = (Debris*)malloc(sizeof(Debris));
			memset(d, 0, sizeof(Debris));
			stage.debrisTail->next = d;
			stage.debrisTail = d;

			d->x = e->x + e->w / 2;
			d->y = e->y + e->h / 2;
            d->dx = -5 + rand() % 11;
			d->dy = -(5 + (rand() % 12));
			d->life = FPS ;

			if(e==player){
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
			d = (Debris*)malloc(sizeof(Debris));
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
static void addPoints(int x, int y)
{
	Entity *e;

	e =(Entity*) malloc(sizeof(Entity));
	memset(e, 0, sizeof(Entity));
	stage.pointsTail->next = e;
	stage.pointsTail = e;

	e->x = x;
	e->y = y;
	e->dx = -(rand() % 5);
	e->dy = (rand() % 5) - (rand() % 5);
	e->health = FPS * 5;
	e->texture = pointsTexture;

	SDL_QueryTexture(e->texture, NULL, NULL, &e->w, &e->h);

	e->x -= e->w / 2;
	e->y -= e->h / 2;
}

static void fireBullet()
{
	Entity *bullet;

	bullet = (Entity*)malloc(sizeof(Entity));
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

	player->reload = 16;
}

static void fireAlienBullet(Entity *e)
{
	Entity *bullet;

	bullet = (Entity*)malloc(sizeof(Entity));
	memset(bullet, 0, sizeof(Entity));
	stage.bulletTail->next = bullet;
	stage.bulletTail = bullet;

	bullet->x = e->x;
	bullet->y = e->y;

	if(e->side == SIDE_ALIEN){
	bullet->texture = alienBulletTexture;
	bullet->side = SIDE_ALIEN;
	bullet->health = 1;
	}
	else {
            if(rand()%2)
            bullet->texture = bossBulletTexture1;
            else bullet->texture = bossBulletTexture2;
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
        e->health--;
        if (e == player)
	{
		playSound(SND_PLAYER_DIE, CH_PLAYER);
	}
	else
	{

	    if(e->side == SIDE_ALIEN){
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
static void spawnEnemies()
{
	Entity *enemy;

	if (--enemySpawnTimer <= 0)
	{
		enemy = (Entity*)malloc(sizeof(Entity));
		memset(enemy, 0, sizeof(Entity));
		stage.fighterTail->next = enemy;
		stage.fighterTail = enemy;

		enemy->x = SCREEN_WIDTH;
		enemy->y = rand() % SCREEN_HEIGHT;
		enemy->texture = enemyTexture;
		SDL_QueryTexture(enemy->texture, NULL, NULL, &enemy->w, &enemy->h);

		enemy->dx = -(2 + (rand() % 2));
        enemy->dy = (-100+rand() % 200);
        enemy->dy /= 100;

		enemySpawnTimer = 30 + (rand() % 60);
		enemy->side = SIDE_ALIEN;
		enemy->health = 1;
		enemy->reload = FPS * (1 + (rand() % 3));
	}
}
static void spawnBoss(){
    if(bossSpawnTimes-- > 0)
    {
    Entity *boss;
    boss = (Entity*)malloc(sizeof(Entity));
    memset(boss, 0, sizeof(Entity));

    boss->texture = bossTexture;
    SDL_QueryTexture(boss->texture, NULL, NULL, &boss->w, &boss->h);
    stage.fighterTail->next = boss;
    stage.fighterTail = boss;
    boss->x = SCREEN_WIDTH;
    boss->y = SCREEN_HEIGHT / 2 - boss->h/2;
    boss->dx --;
    boss->side = SIDE_BOSS;
    boss->health = BOSS_MAX_HEALTH;
    boss->reload = FPS * (1 + (rand() % 3));
    }
}
static void spawnMeteorite(){
    Entity *meteo;
    if(--meteoriteSpawnTimer < 0){
        meteo = (Entity*)malloc(sizeof(Entity));
        memset(meteo, 0, sizeof(Entity));
        stage.meteoTail->next = meteo;
        stage.meteoTail = meteo;

        meteo->texture = meteoriteTexture;
        SDL_QueryTexture(meteo->texture, NULL, NULL, &meteo->w, &meteo->h);
        meteo->x = rand() % SCREEN_WIDTH;
        meteo->y = -meteo->h;
        meteo->dx = -3;
        meteo->dy = 4;
        meteo->health = 1;
        meteoriteSpawnTimer = 2*FPS + rand()% (3*FPS);
    }
}

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


void drawBackground()
{
	SDL_Rect dest;
    dest.x = 0;
    dest.y = 0;
    dest.w = SCREEN_WIDTH;
    dest.h = SCREEN_HEIGHT;
    SDL_RenderCopy(app.renderer,background,NULL,&dest);

}
void drawMeteorite(){
    for(Entity* m = stage.meteoHead.next; m != NULL ; m = m->next){
        blit(m->texture, m->x, m->y);
    }
}
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

static void drawDebris()
{
	Debris *d;

	for (d = stage.debrisHead.next ; d != NULL ; d = d->next)
	{
		blitRect(d->texture, &d->rect, d->x, d->y);
	}
}

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
static void drawBigExplosions()
{
	Explosion *e;

	SDL_SetRenderDrawBlendMode(app.renderer, SDL_BLENDMODE_ADD);
	SDL_SetTextureBlendMode(bigExplosionTexture, SDL_BLENDMODE_ADD);

	for (e = stage.explosionHead.next ; e != NULL ; e = e->next)
	{
		SDL_SetTextureColorMod(bigExplosionTexture, e->r, e->g, e->b);
        SDL_SetTextureAlphaMod(bigExplosionTexture, e->a);

		blit(bigExplosionTexture, e->x, e->y);
	}

    SDL_SetRenderDrawBlendMode(app.renderer, SDL_BLENDMODE_NONE);
}

static void drawFighters()
{
	Entity *e;

	for (e = stage.fighterHead.next ; e != NULL ; e = e->next)
	{
	    if(e == player && e->health != PLAYER_HEALTH){
            blit(e->_texture,e->x,e->y);
	    }else{
	    blit(e->texture, e->x, e->y);
	    }
}}
static void drawBullets()
{
	Entity *b;

	for (b = stage.bulletHead.next ; b != NULL ; b = b->next)
	{
	    if(b->health != 0)
		blit(b->texture, b->x, b->y);
	}
}
static void drawHud()
{
	drawText(10, 10, 255, 255, 255, TEXT_LEFT,"SCORE: %03d", stage.score);
    drawText(10, 50, 255, 0 ,0 ,TEXT_LEFT ,"DEFEAT: %03d", stage.defeat);
	if (stage.score > 0 && stage.score == highscore)
	{
		drawText(960, 10, 0, 255, 0, 2 ,"HIGH SCORE: %03d", highscore);
	}
	else
	{
		drawText(960, 10, 255, 255, 255, 2,"HIGH SCORE: %03d", highscore);
	}
}
static void drawHeart(){
    SDL_Rect rect;

    SDL_QueryTexture(heart,NULL,NULL,&rect.w,&rect.h);
    if(player != NULL){
    if(player->health == PLAYER_HEALTH){
        blit(heart,SCREEN_WIDTH/2-rect.w,0);
        blit(heart,SCREEN_WIDTH/2 + 10,0);
    }else {
        blit(heart,SCREEN_WIDTH/2-rect.w,0);
    }}

}
static void drawPoints()
{
	Entity *e;

	for (e = stage.pointsHead.next ; e != NULL ; e = e->next)
	{
		if (e->health > (FPS *2) || e->health % 12 < 6)
		{
			blit(e->texture, e->x, e->y);
		}
	}
}
static void drawBossBar(){
    drawText(100, SCREEN_HEIGHT - GLYPH_HEIGHT - 5, 255, 255, 255, TEXT_LEFT, "BOSS:");

    SDL_Rect r;
    r.h = 40;
    r.w = BOSS_BAR_LEN -(-boss->health + BOSS_MAX_HEALTH)*(BOSS_BAR_LEN/BOSS_MAX_HEALTH);
    r.x = 200;
    r.y = SCREEN_HEIGHT - 40;
    SDL_SetRenderDrawColor(app.renderer,255, 0, 0, 0);
    SDL_RenderFillRect(app.renderer, &r);

    SDL_SetRenderDrawColor(app.renderer, 255,255,255,0);
    SDL_RenderDrawRect(app.renderer, &r);
}
void drawMouse(){
	blitM(targetTexture,app.mouse.x,app.mouse.y,1);
}

static void draw()
{
    drawBackground();

	drawStarfield();

    if(boss != NULL && BossAppear && boss->health > 0)
	drawBossBar();

	drawPoints();

    drawFighters();

	drawBullets();

	drawDebris();

	drawExplosions();

	drawMeteorite();

	if(app.win){
        drawBigExplosions();
	}
	drawHud();

	drawHeart();

	drawPause();

	drawHome();

	drawMouse();

}
