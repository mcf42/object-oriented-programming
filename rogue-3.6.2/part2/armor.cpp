// implementation for armor
// michael fiander

#include "item.hpp"
#include "rogue.hpp"

void armor::wear()
{
    struct linked_list *item;
    struct object *obj;

    if (cur_armor != NULL) {
	   addmsg("You are already wearing some");
	   if (!terse) {
	       addmsg(".  You'll have to take it off first");
       }
	   endmsg();
    after = FALSE;
	return;
    }

    if ((item = get_item("wear", ARMOR)) == NULL) {
	   return;
    }

    obj = (struct object *) ldata(item);

    if (obj->o_type != ARMOR) {
	   msg("You can't wear that.");
	   return;
    }

    waste_time();

    if (!terse) {
	   addmsg("You are now w");
    }
    else {
	   addmsg("W");
    }

    msg("earing %s.", a_names[obj->o_which]);

    cur_armor = obj;
    obj->o_flags |= ISKNOW;
}

void armor::take_off()
{
    struct object *obj;

    if ((obj = cur_armor) == NULL) {
        if (terse) {
            msg("Not wearing armor");
        }
        else {
            msg("You aren't wearing any armor");
        }
    return;
    }

    if (!dropcheck(cur_armor)) {
        return;
    }

    cur_armor = NULL;

    if (terse) {
        addmsg("Was");
    }
    
    else {
        addmsg("You used to be ");
    }

    msg(" wearing %c) %s", pack_char(obj), inv_name(obj, TRUE));
}