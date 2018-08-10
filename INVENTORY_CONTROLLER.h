#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <ostream>


#include "Leadwerks.h"
#include "UI_MAIN.h"

#include <fstream>


enum ITEM_TYPE { MEDKIT, FOOD, WEAPON_AR, WEAPON_PISTOL, AMMO_AR, AMMO_PISTOL, ANTIRAD, AK_MAG, PM_MAG };
class item
{
public:
	std::string name;
	ITEM_TYPE type;
	int count;
	item(std::string name, ITEM_TYPE type, int count) :name(name), type(type), count(count) {};

};



class INVENTORY_CONTROLLER
{
	Leadwerks::Context *current_context;
public:
	INVENTORY_CONTROLLER();
	~INVENTORY_CONTROLLER();

	//void drawTexts();
	//void drawHUD();
	INVENTORY_CONTROLLER GET_CURRENT_INVENTORY();
	void load_inventory() { load_config(); }
	void update_inventory(ITEM_TYPE t);
	void add_item(std::string name, ITEM_TYPE type, int count);
	void delete_item(ITEM_TYPE type);
	friend item get_item(ITEM_TYPE type);
	void load_config();
	void parse(std::string string);
	ITEM_TYPE GET_TYPE(std::string type);
	std::string GET_TYPES(ITEM_TYPE type);
	void use(ITEM_TYPE t);
	void save_config();
};

