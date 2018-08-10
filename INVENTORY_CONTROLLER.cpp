#include "INVENTORY_CONTROLLER.h"
#include "UI_MAIN.h"
#include <Leadwerks.h>

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

std::vector<item> inventory_pack;

INVENTORY_CONTROLLER::INVENTORY_CONTROLLER()
{
	inventory_pack.clear();
}


INVENTORY_CONTROLLER::~INVENTORY_CONTROLLER()
{
}

void INVENTORY_CONTROLLER::use(ITEM_TYPE t)
{
	lua_State* L;
	L = lua_open();
	luaL_openlibs(L);
	//luaL_dofile(L, "add.lua");
	lua_getglobal(L, "heal");
	for (int i = 0; i < inventory_pack.size(); i++)
	{
		if (inventory_pack[i].type == t)
		{
			if (inventory_pack[i].count > 0)
			{
				inventory_pack[i].count--;
			}
		}
	}
	save_config();
	load_config();
	//for (auto temp : inventory_pack)
	//{
	//	if (t == temp.type) {
	//		
	//		if (temp.count > 0) { 
	//			
	//			inventory_pack[0].count--;//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//			//std::cout << "Used!" << inventory_pack[0].count << "\n";
	//		} 
	//	}
	//}
}

void INVENTORY_CONTROLLER::load_config()
{
	std::string temp;
	inventory_pack.clear();
	std::ifstream config("inventory.cfg");
	if (config.is_open())
	{
		while (getline(config, temp))
		{
			parse(temp);
		}
		current_context = Leadwerks::Context::GetCurrent();
	}
	else {
		std::cout << "Error loading config!";
	}
	config.close();
}
void INVENTORY_CONTROLLER::parse(std::string string)
{
	std::string TYPE;
	std::string value;
	std::string temp_t;
	int count = 0;
	int temp = 0;
	if (string[temp] == '[')
	{
		temp++;
		while (string[temp] != ']')
		{

			TYPE += string[temp];
			//TYPE[temp + 1] = ']';
			temp++;
		}
		while (string[temp] != '~')
		{
			temp++;
			if (string[temp] == ':')
			{
				temp++;
				while (string[temp] != ';')
				{
					value += string[temp];
					temp++;
				}
			}
			if (string[temp] == '(')
			{
				temp++;
				while (string[temp] != ')')
				{
					temp_t += string[temp];
					temp++;
				}
				count = stoi(temp_t);
			}



			//value += string[temp];
		}

	}
	add_item(value, GET_TYPE(TYPE), count);
}

ITEM_TYPE INVENTORY_CONTROLLER::GET_TYPE(std::string type)
{
	if (type == "MEDKIT")
	{
		return MEDKIT;
	}
	if (type == "ANTIRAD")
	{
		return ANTIRAD;
	}
	else if (type == "FOOD")
	{
		return FOOD;
	}
	else if (type == "WEAPON_AR")
	{
		return WEAPON_AR;
	}
	else if (type == "WEAPON_PISTOL")
	{
		return WEAPON_PISTOL;
	}
	else if (type == "AMMO_AR")
	{
		return AMMO_AR;
	}
	else if (type == "AMMO_P")
	{
		return AMMO_PISTOL;
	}

}

std::string INVENTORY_CONTROLLER::GET_TYPES(ITEM_TYPE type)
{
	if (type == MEDKIT)
	{
		return "MEDKIT";
	}
	if (type == ANTIRAD)
	{
		return "ANTIRAD";
	}
	else if (type == FOOD)
	{
		return "FOOD";
	}
	else if (type == WEAPON_AR)
	{
		return  "WEAPON_AR";
	}
	else if (type == WEAPON_PISTOL)
	{
		return "WEAPON_PISTOL";
	}
	else if (type == AMMO_AR)
	{
		return "AMMO_AR";
	}
	else if (type == AMMO_PISTOL)
	{
		return "AMMO_P";
	}
}

void INVENTORY_CONTROLLER::add_item(std::string name, ITEM_TYPE type, int count)
{
	item newitem(name, type, count);
	inventory_pack.push_back(newitem);
	if (type == ITEM_TYPE::AMMO_AR)
	{

	}
//	TEMPORARY_UI_MAIN->add_texts(std::to_string(count), 317, 260);
}

void INVENTORY_CONTROLLER::update_inventory(ITEM_TYPE t)
{
	for (auto temp : inventory_pack)
	{
		if (temp.type == t)
		{
			if (temp.count < 1)
			{
				delete_item(t);
			}

		}

	}
}

void INVENTORY_CONTROLLER::delete_item(ITEM_TYPE type)
{
	int t = 0;
	for (auto temp : inventory_pack)
	{
		t++;
		if (temp.type == type)
		{
			inventory_pack.erase(inventory_pack.begin(), inventory_pack.begin() + t);
		}
	}
}

item get_item(ITEM_TYPE type)
{
	for (auto temp : inventory_pack)
	{
		if (temp.type == type)
		{
			return temp;
		}
	}
}

void INVENTORY_CONTROLLER::save_config()
{
	
	ofstream config("inventory.cfg", std::ios::out | std::ios::trunc);
	std::string tempo="";
	for (auto temp : inventory_pack)
	{
		tempo = "";
		tempo = "[" + GET_TYPES(temp.type) + "]" + "N:" + temp.name + ";" + "C(" + std::to_string(temp.count) + ")~\n";
		config << tempo;
	}
	config.close();
}

INVENTORY_CONTROLLER INVENTORY_CONTROLLER::GET_CURRENT_INVENTORY()
{
	return *this;
}
