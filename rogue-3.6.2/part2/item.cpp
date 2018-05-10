// implementation for items
// michael fiander

#include "item.hpp"
#include "rogue.hpp"

void object::wear() {
	msg("You can't wear that.");
}

void object::wield() {
	msg("You can't wield that.");
}

void object::missile() {
	msg("You can't throw that.");
}

void object::quaff() {
	msg("Yuk! Why would you want to drink that?");
}

void object::ring_on() {
	msg("It would be difficult to wrap that around a finger.");
}

void object::ring_off() {
	msg("Not wearing such a ring.");
}

void object::read_scroll() {
	msg("There is nothing on it to read.")
}

void object::waste_time() {
	do_daemons(BEFORE);
	do_fuses(BEFORE);
	do_daemons(AFTER);
	do_fuses(AFTER);
}