/*
Farming function source code for farming mod for Quake 2
*/

//#include "q_shared.h"
//#include "g_local.h"
#include "f_farm.h"

// Touch function for seed bullet
void
spawner_touch(edict_t *self, edict_t *other, cplane_t *plane, csurface_t *surf)
{
	(void)plane; // Not used
	if (other == self->owner)
		return;

	if (surf && (surf->flags & SURF_SKY))
	{
		G_FreeEdict(self);
		return;
	}

	if (self->owner->client)
		PlayerNoise(self->owner, self->s.origin, PNOISE_IMPACT);

	switch (self->shop_mode) {
	case 0:
		if (self->owner->currency < 10) {
			Com_Printf("Soldier seeds cost $10\n");
			return;
		}
		self->owner->currency -= 10;
		break;
	case 1:
		if (self->owner->currency < 20) {
			Com_Printf("Brain seeds cost $20\n");
			return;
		}
		self->owner->currency -= 20;
		break;
	case 2:
		if (self->owner->currency < 50) {
			Com_Printf("Chick seeds cost $50\n");
			return;
		}
		self->owner->currency -= 50;
		break;
	case 3:
		if (self->owner->currency < 200) {
			Com_Printf("Berserker seeds cost $200\n");
			return;
		}
		self->owner->currency -= 200;
		break;
	default:
		if (self->owner->currency < 1000) {
			Com_Printf("Gladiator seeds cost $1000\n");
			return;
		}
		self->owner->currency -= 1000;
		break;
	}
	edict_t *monster = G_Spawn();
	monster->farm_animal = 1;
	monster->monsterinfo.next_water_time = level.time;
	monster->monsterinfo.next_fert_time = level.time;
	monster->monsterinfo.next_prune_time = level.time;
	monster->monsterinfo.water_time = 10;
	monster->monsterinfo.fert_time = 60;
	monster->monsterinfo.prune_time = 5;
	monster->monsterinfo.farmer = self->owner;
	switch (self->shop_mode) {
	case 0:
		monster->monsterinfo.produce_time = 12;
		monster->monsterinfo.produce_val = 1;
		SP_monster_soldier(monster);
		break;
	case 1:
		monster->monsterinfo.produce_time = 30;
		monster->monsterinfo.produce_val = 3;
		SP_monster_brain(monster);
		break;
	case 2:
		monster->monsterinfo.produce_time = 40;
		monster->monsterinfo.produce_val = 5;
		SP_monster_chick(monster);
		break;
	case 3:
		monster->monsterinfo.produce_time = 60;
		monster->monsterinfo.produce_val = 8;
		SP_monster_berserk(monster);
		break;
	default:
		monster->monsterinfo.produce_time = 200;
		monster->monsterinfo.produce_val = 30;
		SP_monster_gladiator(monster);
		break;
	}
	monster->max_health = monster->health;
	monster->monsterinfo.next_produce_time = level.time + self->monsterinfo.produce_time;
	VectorCopy(self->s.origin, monster->s.origin);
	

	G_FreeEdict(self);
}

// Fires a seed bullet
void
fire_plant(edict_t *self){
	vec3_t dir;
	AngleVectors(self->client->v_angle, dir, NULL, NULL);

	edict_t *bolt = G_Spawn();
	bolt->svflags = SVF_DEADMONSTER;
	// yes, I know it looks weird that projectiles are deadmonsters
	// what this means is that when prediction is used against the object
	// (blaster/hyperblaster shots), the player won't be solid clipped against
	// the object.  Right now trying to run into a firing hyperblaster
	// is very jerky since you are predicted 'against' the shots.
	VectorCopy(self->s.origin, bolt->s.origin);
	VectorCopy(self->s.origin, bolt->s.old_origin);
	vectoangles(dir, bolt->s.angles);

	VectorScale(dir, 1000, bolt->velocity);
	bolt->movetype = MOVETYPE_FLYMISSILE;
	bolt->clipmask = MASK_SHOT;
	bolt->s.effects |= EF_BLASTER;
	bolt->solid = SOLID_BBOX;
	VectorClear(bolt->mins);
	VectorClear(bolt->maxs);
	bolt->s.modelindex = gi.modelindex("models/objects/laser/tris.md2");
	bolt->s.sound = gi.soundindex("misc/lasfly.wav");
	bolt->owner = self;
	bolt->touch = spawner_touch;
	bolt->nextthink = level.time + 2;
	bolt->think = G_FreeEdict;
	bolt->dmg = 0;
	bolt->classname = "bolt";

	gitem_t *weapon = self->client->pers.weapon;
	if (weapon == FindItem("railgun"))
		bolt->shop_mode = 1;
	else if (weapon == FindItem("chaingun"))
		bolt->shop_mode = 2;
	else if (weapon == FindItem("shotgun"))
		bolt->shop_mode = 3;
	else if (weapon == FindItem("bfg10k"))
		bolt->shop_mode = 4;
	else
		bolt->shop_mode = 0;

	gi.linkentity(bolt);
	trace_t tr = gi.trace(self->s.origin, NULL, NULL, bolt->s.origin, bolt, MASK_SHOT);
	if (tr.fraction < 1.0)
	{
		VectorMA(bolt->s.origin, -10, dir, bolt->s.origin);
		bolt->touch(bolt, tr.ent, NULL, NULL);
	}
}