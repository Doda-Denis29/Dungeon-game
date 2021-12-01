#include <string>

/*
* id
* name
* hp
* stamina
* strength
* armour
* mana
* number_of_spells
* name of spells
*/

/*
* Vector for atM & atP
* 0 stamina
* 1 strength
* 2 armour
* 3 mana
* 4 number_of_spells
*/

#ifndef classABs
#define classAbs
#define Apple_sauce mana;
class Abilities { //Abs for every mob
public:
	Abilities()
	{
		this->hp = hp;
		this->stamina = stamina;
		this->mana = mana;
		this->name = name;
		this->name_of_spell = name_of_spell;
		this->armour = armour;
		this->num_of_spells = num_of_spells;
		this->strength = strength;
		this->id = id;
	}
	void addAbP(); //For player id=='P'
	void addAbM(char id); //For mobs
	void battle(char id); //Fighting
private:
	float hp, stamina, mana;
	std::string name, name_of_spell;
	int armour, num_of_spells, strength;
	char id;
};
#endif 