Readme
Michael Fiander

an abstraction of rogue

Armor

	Armor is a type of item found in the dungeon. It is equipable by the
player. Armor has six classes that are ranked by protetion from 2 to 7: leather
armor, studded leather armor/ring mail, scale mail, chain mail, banded/splint
mail, and plate mail, respectively. Only one set of armor may be worn at at a
time. Armor can be blessed (class goes up) or cursed. (class goes down and is
unequipable) Putting on and taking off armor takes a turn(?) Functions for
putting on and taking off armor are in armor.c.

Monsters

	Monsters are found the the dungeon. If they are aggressive, they will
chase the player. If the player is in the same room as the monster, it will
find a temporary destination one tile away(?) to move to in order to reach the
player. If the player is in a different room, it will find the nearest entrance
that will take it to the player room and move to that room. If it is confused,
it will move randomly. If it is scared, it will have other behavior. (check
this again) Functions for this are found in chase.c. Monsters have ranks in
power and have properties such as: carrying item, behavior flags, strength, HP,
exp given, level, armor, vorpal rank and damage. The deeper the level, stronger
monsters will be generated. This information is in monster.c. 

Player Commands

	Player commands are handled by functions in command.h. Its primary
function uses switch statements to take the program to seperate functions
that correlate with every key press (i.e. pressing 'e' will use a switch to use
eat().

Daemons

	Daemons are things in the game the player cannot see or have control
over. This includes the player recovering HP after a certain number of turns,
when wandering monsters will move, when the player will come out of confusion,
when the player will go blind or recover his vision, when he will lose haste,
when he will lose invisible sight, the digestion of his food and when he will
faint from hunger. Functions that control Daemons are in daemons.c.

Fuses

	Fuses are events that will happen in the future. Fuses are Daemons that
are held in a table. Each turn will tick down the fuse to when the action will
happen. Certain events will lengthen a fuse's timer. daemon.c.

Combat

	The player fights monsters in Rogue. This is done by moving into them.
Both the player and the monster will take a swing each turn which can hit or
miss. Special monsters have special effects such as stealing gold when they hit
you. When the player or the monster reaches 0 HP, they will die unless they
make a saving throw. If a monster has items, it will drop them when it dies.
Some monsters can regenerate HP in battle. The player can also throw items at
monsters or shoow them with arrows. Functions for combat are found in fight.c

The Character

	The character starts the game on floor 1. He is level 1 and has a few
items in his inventory. This is in main.c. The player can move the character in
9 directions. The game will detect if a move is legal or not. if the character
is confused, he will move in a random direction when commanded. If a player
moves onto a trap, certain effects will be triggered. If a room is illuminated,
the character will be able to see the entire room and everything that is not
hidden in it. When he moves out, the room will come of of view, everything that
can move will dissapear from the screen. The character can run. (continue in a
direction until something happens) This is found in move.c. The character can
also search for hidden traps, items and doors. In Rogue, the player also
collects gold that equates to the player's score.

The World

	When the character goes to a new level, rooms in the new level are
randomly generated. A staircase is added to a random room, traps are added
to random rooms, gold and items are also added to random rooms. Rooms are generated
by functions in newlevel.c and rooms.c.
	Passages are added after the rooms have been created. Rooms are chosen
one by one and passages are randomly dug between adjacent rooms. The entrances
to rooms may or may not be visible or hidden.

The Pack

	The player has a pack that items are stored in. Items are automatically
picked up when walked over. Items can be dropped from the pack. The pack has a
limit of items that can be carried. (how number determined?) Multiples of the same
item are stored in the same slot. Functions for handling the pack are using
items from it are stored in pack.c. The way items appear in the pack is
determined by things.c. The player's gold is also handled by things.c.

Weapons

	Weapons are equippable by the player and are naturally used to fight
monsters found in the dungeons of doom. Weapons are divided into melee and
missile types. Melee weapons are roughly ranked by power and range from daggers
to two-handers. They have damage values when wielded and swung and when thrown
as missiles. Missile weapons have damage values. Items such as throwing knives
can be thrown. Arrows and bolts can be thrown as projectiles when a bow or
crossbow is equipped. (they can also be thrown regularly although with mediocre
effect) Weapons can be blessed (more damage) or cursed. (less damage and
unequippable) Functions dealing with weapons can be found in weapons.c.

Magic Items

Magic items are many and varied in type and effect and are listed here.

	Potions: potions have random colors and random effects that are unknown
		to the player. Once the character has drinken a potion of
		certain color, he will remember it's effect. These effects can
		be good or bad. potions.c.
	Scrolls: scrolls have random names and random effects that are unknown
		to the player. Once the character has read the a scroll, he
		will remember it's effect. The effects can be good or bad.
		scrolls.c
	Rings: rings have random gemstones and random effects that are unknown
		to the player. The player cannot identify a ring by putting it
		on. A ring can be worn on the left and right hand. Each type
		of ring will take an ammount of food points per turn while
		equipped. rings.c.
	Staves/Wands: Staves and wands have random materials and unknown uses.
		The player can zap a wand from his inventory in a direction and
		the wand's effect will shoot in that direction. Once the wand/
		staff has been used, the player will remember it. sticks.c.
