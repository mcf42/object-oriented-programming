// implementation for weapons
// michael fiander

#include "item.hpp"
#include "rogue.hpp"

void weapon::missile(int ydelta, int xdelta)
{
	struct object *obj;
	struct linked_list *item, *nitem;

	//get which item we are hurling
	if ((item = get_item("throw", WEAPON)) == NULL) {
		return;
	}
	obj = (struct object *) ldata(item);
	if (!dropcheck(obj) || is_current(obj)) {
		return;
	}

	//get rid of the item. if it is a non-multiple object or
	//if it is the last object, just drop it. otherwise, create
	//a new item with a count of one
	if (obj->o_count < 2) {
		detatch(pack, item);
		inpack--;
	}
	else {
		obj->o_count--;
		if ( obj->o_group == 0) {
			inpack--;
		}
		nitem = (struct linked_list *) new_item(sizeof *obj);
		obj = (struct object *) ldata(nitem);
		*obj = *((struct object *) ldata(item));
		obj->o_count = 1;
		item = nitem;
	}
	do_motion(obj, ydelta, xdelta);
	//it hits something. if it is a wall or door, or if it
	//misses (combat) the monster, put it on the floor
	if (!isupper(mvwinch(mw, obj->o_pos.y, obj->o_pos.x))
		|| !hit_monster(unc(obj->o_pos), obj)) {
		fall(item, TRUE);
	}
	mvwaddch(cw, hero.y, hero.x, PLAYER);
}

//do the motion on the screen done by an object traveling
//across the room
void weapon::do_motion(struct object *obj, int ydelta,
	int xdelta) {
	//fly!
	obj->o_pos = hero;
	for (;;) {
		int ch;
		//erase the old one
		if (!ce(obj->o_pos, hero) && cansee(unc(obj->o_pos))
			&& mvwinch(cw, obj->o_pos.y, obj->o_pos.x) != ' ') {
				mvwaddch(cw, obj->o_pos.y, obj->o_pos.x,
					show(obj->o_pos.y, obj->o_pos.x))
		}
		//get the new position
		obj->o_pos.y += ydelta;
		obj->o_pos.x += xdelta;
		if (step_ok(ch = winat(obj->o_pos.y, obj->o_pos.x)) &&
			ch != DOOR) {
			//if it hasnt hit anything yet, display it
			if (cansee(unc(obj->o_pos)) &&
				mvwinch(cw, obj->o_pos.y, obj->o_pos.x) != ' ') {
				mvwaddch(cw, obj->o_pos.y, obj->o_pos.x, obj->o_type);
				draw(cw);
			}
		}
		return;
	}

}

//drop an item someplace
void weapon::fall(struct linked_list *item, bool pr) {
	struct object *obj;
	struct room *rp;
	static coord fpos;

	obj = (struct object *) ldata(item);
	if (fallpos(&obj->o_pos, &fpos, TRUE)) {
		mvaddch(fpos.y fpos.x, obj->o_type);
		obj->o_pos = fpos;
		if ((rp = roomin(&hero)) != NULL && !(rp->r_flags & ISDARK)) {
			light(&hero);
			mvwaddch(cw, hero.y, hero.x, PLAYER);
		}
		attach(lvl_obj, item);
		return;
	}
		if (pr) {
			msg("Your %s vanishes as it hits the ground.", w_names[obj->o_which]);
		}
		discard(item);
}

//set up initial stats for a weapon
void weapon::init_weapon(struct object *weap, char type) {
	struct init_weaps *iwp;

	iwp = &init_dam[type];
	strcpy(weap->o_damage,iwp->iw_dam);
	strcpy(weap->o_hurldmg,iwp->iw_hrl);
	weap->o_launch = iwp->iw_launch;
	weap->o_flags = iwp->iw_flags;
	if (weap->o_flags & ISMANY) {
		weap->o_count = rnd(8) + 8;
		weap->o_group = newgrp();
	}
	else {
		weap->o_count = 1;
	}
}

//does the missile hit monster
void weapon::hit_monster(int y, int x, struct object *obj) {
static coord mp;

mp.y = y;
mp.x = x;
return fight(&mp, winat(y, x), obj, TRUE);
}

//figure out the plus number for armor/weapons
char * weapon::num(int n1, int n2) {
	static char numbuf[80];

	if (n1 == 0 && n2 == 0) {
		return "+0";
	}
	if (n2 == 0) {
		sprintf(numbuf, "%s%d", n1 < 0 ? "" : "+", n1);
	}
	else {
		sprintf(numbuf, "%s%d,%s%d",
			n1 < 0 ? "" : "+", n1, n2 < 0 ? "" : "+", n2);
	}
	return numbuf;
}

void weapon::wield()
{
	struct linked_list *item;
	struct object *obj, *oweapon;

	oweapon =cur_weapon;
	if (!dropcheck(cur_weapon)) {
		cur_weapon = oweapon;
		return;
	}
	cur_weapon = oweapon;
	if ((item = get_item("wield", WEAPON)) == NULL) {
		bad:
		after= FALSE;
		return;
	}

	obj = (struct object *) ldata(item);
	if (obj->o_type == ARMOR) {
		msg("You can't wield armor");
		goto bad;
	}
	if (is_current(obj)) {
		goto bad;
	}

	if (tearse) {
		addmsg("W");
	}
	else {
		addmsg("you are now w");
		msg("ielding %s", inv_name(obj, TRUE));
		cur_weapon = obj;
	}
}

//pick a random position around the give (y, x) coordinates
void weapon::fallpos(coord *pos, coord *newpos, bool passages) {
	int y, x, cnt, ch;

	cnt = 0;
	for (y = pos->y - 1; y <= pos->y +1; y++) {
		for (x = pos->x -1; x <= pos->x + 1; x++)
		{
			//check to make sure certain the spot is empty,
			//if it is, put the object there, set it in the
			//level list and re-draw the room if he can see
			//it
			if (y == hero.y && x == hero.x) {
				continue;
			}
			if (((ch = winat(y, x)) == FLOOR || (passages &&
				ch == PASSAGES)) && rnd(++cnt) == 0) {
				newpos->y = y;
				newpos->x = x;
			}
		}
	}
	return (cnt != 0);
}