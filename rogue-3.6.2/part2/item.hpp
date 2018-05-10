// item definition
// michael fiander

#include "item.hpp"
#include "rogue.hpp"

class object {
	void pick_up();
	void drop();

	virtual void wear();

	virtual void wield();
	virtual void missile();

	virtual void waste_time();

	virtual void quaff();

	virtual void ring_on();

	virtual void read_scroll();

	virtual void zap(bool);
};

class item : object {
private:
	int o_type;				/* What kind of object it is */
	coord o_pos;			/* Where it lives on the screen */
	char o_launch;			/* What you need to launch it */
	char o_damage[8];		/* Damage if used like sword */
	char o_hurldmg[8];		/* Damage if thrown */
	int o_count;			/* Count for plural objects */
	int o_which;			/* Which object of a type it is */
	int o_hplus;			/* Plusses to hit */
	int o_dplus;			/* Plusses to damage */
	int o_ac;				/* Armor class */
	int o_flags;			/* Information about objects */
	int o_group;			/* Group number for this object */
};

class magic_item : object {
private:
	char mi_name[30];
	int mi_prob;
	int mi_worth;
};

class armor : item {
private:

public:
	void wear() override;
	void take_off();
};

class weapon : item {
private:
	static int MAXWEAPONS = 12;

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

	static struct initial_weapons {
		char* iw_damage; // damage
		char* iw_hurl; // hurl damage
		char* iw_launch; // what it launches with
		int iw_flags;
	};

	init_dam[MAXWEAPONS] = {
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
	void missile(int, int) override;
	void wield() override;
	
	void do_motion(object, int, int);
	void fall(linked_list*, bool);
	void init_weapon(object*, char);
	void hit_monster(int, int, object*);
	char* num(int, int);
	void fallpos(coord *, coord *, bool);
};

class potion : magic_item {
private:
public:
	void quaff() override;
};

class ring : magic_item {
private:
public:
	void ring_on() override;
	void ring_off() override;

	void gethand();
	int ringeat();
	int ring_num(object *);
};

class scroll : magic_item {
	void read_scroll() override;
};

class stick : magic_item {
	void zap(gotdir) override;

	void fix_stick(object*);
	void drain(int, int, int, int);
	char* charge_str(object*);
};