#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "Leadwerks.h"

enum ITEM_TYPE { MEDKIT, FOOD, WEAPON_AR, WEAPON_PISTOL, AMMO_AR, AMMO_PISTOL, ANTIRAD, AK_MAG, PM_MAG };

class item
{
public:
	std::string name;
	ITEM_TYPE type;
	int count;
	Leadwerks::Vec2 pos;
	item(std::string name, ITEM_TYPE type, int count) :name(name), type(type), count(count) {
		switch (type)
		{
		case ITEM_TYPE::MEDKIT:
			pos = Leadwerks::Vec2(340, 260);
			break;
		case 1:
			pos = Leadwerks::Vec2(700, 300);
			break;
		case 2:
			pos = Leadwerks::Vec2(900, 300);
			break;
		case 3:
			pos = Leadwerks::Vec2(1700, 300);
			break;
		case ITEM_TYPE::AMMO_AR:
			pos = Leadwerks::Vec2(245, 360);
			break;
		case 5:
			pos = Leadwerks::Vec2(1100, 300);
			break;break;
		case ITEM_TYPE::ANTIRAD:
			pos = Leadwerks::Vec2(245, 260);
			break;
			break;
		case 7:
			pos = Leadwerks::Vec2(4020, 300);
			break;
		case 8:
			pos = Leadwerks::Vec2(4200, 300);
			break;
		default:
			pos = Leadwerks::Vec2(5200, 400);
		}
	}
};
class inventory
{
	std::vector<item*> inventory_pack;
	Leadwerks::Context *current_context;
public:
	bool isSomthChecked;
	Leadwerks::Vec2 current_checked_item;
	void drawTexts();
	void drawText(std::string text, Leadwerks::Vec2 pos);
	void drawHUD();
	inventory GET_CURRENT_INVENTORY();
	void load_inventory() { load_config(); }
	void update_inventory(ITEM_TYPE t);
	void add_item(std::string name, ITEM_TYPE type, int count);
	void delete_item(ITEM_TYPE type);
	void load_config();
	void parse(std::string string);
	ITEM_TYPE GET_TYPE(std::string type);
	std::string GET_TYPES(ITEM_TYPE type);
	void use(ITEM_TYPE t);
	void use(Leadwerks::Vec2 pos);
	bool isInRect(Leadwerks::Vec2 rect, Leadwerks::Vec2 point, Leadwerks::Vec2 rect_size);
	void save_config();

	void chooseInvItem(Leadwerks::Vec2 pos);
	bool isCheckedAllready(Leadwerks::Vec2 n_pos);
	
};

