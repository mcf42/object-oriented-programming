// new c++ class for weapons
// michael fiander

static int MAXWEAPONS = 12;

class weapon {
private:
	//possible types of weapons
	std::string weapon_names[MAXWEAPONS] = {
		"mace",
		"long sword",
		"short bow",
		"arrow",
		"dagger",
		"rock",
		"two handed sword",
		"sling",
		"dart",
		"crossbow",
		"crossbow bolt",
		"spear",
	}

	//initial weapon stats
	static struct initial_weapons {
		char *iw_dam; //damage
		char *iw_hrl; //hurl damage
		char iw_launch; //what it launches with
		int iw_flags;
	} init_dam[MAXWEAPONS] = {
		"2d4", "1d3", NONE, 0, //Mace
		"1d10", "1d2", NONE,0, //Long sword
		"1d1", "1d1", NONE,	0, //Bow
		"1d1", "1d6", BOW,	ISMANY|ISMISL, //Arrow
		"1d6", "1d4", NONE,	ISMISL, //Dagger
		"1d2", "1d4", SLING,ISMANY|ISMISL, //Rock
		"3d6", "1d2", NONE,	0, //2h sword
		"0d0", "0d0", NONE, 0, //Sling
		"1d1", "1d3", NONE,	ISMANY|ISMISL, //Dart
		"1d1", "1d1", NONE, 0, //Crossbow
		"1d2", "1d10", CROSSBOW, ISMANY|ISMISL, //Crossbow bolt
		"1d8", "1d6", NONE, ISMISL, //Spear
	}

public:
	void missile(int, int);
	void do_motion(register struct object, register int,
		register int);
	void fall(register struct linked_list*, bool);
	void init_weapon(register struct object*, char type);
	void hit_monster(register int, register int, struct object*);
	char * num(register int, register int);
	void wield();
	void fallpos(register coord *, register coord *, register bool);
};


void weapon::missile(int ydelta, int xdelta)
{
	register struct object *obj;
	register struct linked_list *item, *nitem;

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
void weapon::do_motion(register struct object *obj, register int ydelta,
	register int xdelta) {
	//fly!
	obj->o_pos = hero;
	for (;;) {
		register int ch;
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
void weapon::fall(register struct linked_list *item, bool pr) {
	register struct object *obj;
	register struct room *rp;
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
void weapon::init_weapon(register struct object *weap, char type) {
	register struct init_weaps *iwp;

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
void weapon::hit_monster(register int y, register int x, struct object *obj) {
static coord mp;

mp.y = y;
mp.x = x;
return fight(&mp, winat(y, x), obj, TRUE);
}

//figure out the plus number for armor/weapons
char * weapon::num(register int n1, register int n2) {
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
	register struct linked_list *item;
	register struct object *obj, *oweapon;

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
void weapon::fallpos(register coord *pos, register coord *newpos, register bool passages) {
	register int y, x, cnt, ch;

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