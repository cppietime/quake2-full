/*
Header file for farming mod for Quake 2
*/

#ifndef _H_F_FARM
#define _H_F_FARM

#include "g_local.h"

// Something to enable spawning the monster
void
SP_monster_berserk(edict_t *self);
void
SP_monster_brain(edict_t *self);
void
SP_monster_chick(edict_t *self);
void
SP_monster_gladiator(edict_t *self);
void
SP_monster_soldier(edict_t *self);

// Touch function for seed bullet
void
spawner_touch(edict_t *self, edict_t *other, cplane_t *plane, csurface_t *surf);

// Fires a seed bullet
void
fire_plant(edict_t *self);

#endif