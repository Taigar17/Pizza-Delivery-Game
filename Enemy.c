#include "common.h"
/*This is the code for the game enemies*/

static void tick(void);
static void touch(Entity* other);
void initGhost(char* line);

void initGhost(char* line)
{
	// Entity is the name of the struct
	Entity* e;
	e = malloc(sizeof(Entity));
	memset(e, 0, sizeof(Entity)); //appended to the list
	stage.entityTail->next = e;
	stage.entityTail = e;

	sscanf(line, "%*s %f %f", &e->x, &e->y);

	e->health = 1; // Positive means drawn on screen
	e->texture = loadTexture("gfx/Ghost_Enemy.png");
	
	SDL_QueryTexture(e->texture, NULL, NULL, &e->w, &e->h);
	e->w /= 4;
	e->h /= 4;

	// It flies in the air 
	e->flags = EF_WEIGHTLESS;
	e->tick = tick;
	e->touch = touch; //Player touches enemy
}

static void tick(void)
{
	self->value += 0.1;
	self->y += sin(self->value);
}

static void touch(Entity* other)
{
	if (self->health > 0 && other == player)
	{
		player->health = 0;
		printf("You have died"); //Outputs in console
		exit(1);
	}
}

//Add doGhost() func to follow players direction 