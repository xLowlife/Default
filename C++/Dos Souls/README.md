# Dos Souls
Folder for Dos Souls

Dos Souls Details:
A game where 2 opponents fight to the death in a series of multi-rounded
games of Rock, Paper, Scissors matches until 1 person's health reaches 0.

The game is played in the format of Attack, Block, Dodge,
and runs on a system of Stamina which is a
resource required to be able to perform an Attack, Block, or Dodge.

If a person does NOT have enough stamina to Attack, Block, or Dodge,
they must "Wait" which is a state of no action leaving them open to being attacked,
but allowed to regain Stamina while spending 0 Stamina.

The player engages in combat 1 stage, named Floor(s), at a time
for a specifed amount of Floors (Default is 10 Floors).

The player enters 1 Floor at a time, and each floor has
a specifed amount of Enemies per Floor (Default is 1 Enemy per Floor).

Game Rules:
Attack	beats	Block	-	Attacker deals Damage to Blocker divided by block strength.
Block	beats	Dodge	-	Blocker deals Damage to Dodger.
Dodge	beats	Attack	-	Dodger deals Damage to Attacker.

If a Blocker Blocks an Attack, and the Blocker's Stamina reaches 0 or Lower,
Blocker gets Stunned, and Attacker deals ANOTHER UNBlocked Damage to Blocker.
Being a Waiter instead of a Blocker is the only way to avoid this.

Game Notes:
Combat is augmented with a system of Items in the form of Weapons and Armor.
Combat Difficulty increases as the player progresses through floors.
