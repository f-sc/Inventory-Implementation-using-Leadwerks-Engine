#include "INV_CONTROLLER.h"



void inventory::use(ITEM_TYPE t)
{
	for (int i = 0; i < inventory_pack.size(); i++)
	{
		if (inventory_pack[i]->type == t)
		{
			if (inventory_pack[i]->count > 0)
			{
				inventory_pack[i]->count--;
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

bool inventory::isInRect(Leadwerks::Vec2 rect, Leadwerks::Vec2 point, Leadwerks::Vec2 rect_size)
{
	for (int x = rect.x; x < rect.x + rect_size.x; x++)
	{
		for (int y = rect.y; y < rect.y + rect_size.y; y++)
		{
			if (point.x == (x - 60) && point.y == (y - 60))
			{
				return true;
			}
		}
	}
	return false;
}

bool inventory::isCheckedAllready(Leadwerks::Vec2 n_pos)
{
	//if()
	return true;
}

void inventory::use(Leadwerks::Vec2 pos)
{
	for (int i = 0; i < inventory_pack.size(); i++)
	{
		if (isInRect(inventory_pack[i]->pos, pos, Leadwerks::Vec2(97, 85)))
		{
			current_context->SetColor(0.0, 0.0, 1.0);
			//current_context->DrawRect(inventory_pack[i]->pos.x-60, inventory_pack[i]->pos.y-60, 97, 85, 0);
			//current_context->Sync();
			if (inventory_pack[i]->count > 0)
			{
				inventory_pack[i]->count--;
			}
		}
	}
	save_config();
	load_config();
}

void inventory::chooseInvItem(Leadwerks::Vec2 pos)
{
	for (int i = 0; i < inventory_pack.size(); i++)
	{
		if (isInRect(inventory_pack[i]->pos, pos, Leadwerks::Vec2(97, 85)))
		{
			if (inventory_pack[i]->count > 0)
			{
				current_context->SetColor(0.0, 0.0, 1.0);
			}
			else
			{
				current_context->SetColor(1.0, 0.0, 0.0);
			}
			current_checked_item = Leadwerks::Vec2(inventory_pack[i]->pos);
			current_context->DrawRect(inventory_pack[i]->pos.x - 60, inventory_pack[i]->pos.y - 60, 97, 85, 0);
			current_context->Sync();
		}
	}
}

void inventory::load_config()
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
void inventory::parse(std::string string)
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

ITEM_TYPE inventory::GET_TYPE(std::string type)
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
}

 std::string inventory::GET_TYPES(ITEM_TYPE type)
{
	if (type == MEDKIT )
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
}

void inventory::add_item(std::string name, ITEM_TYPE type, int count)
{
	item* newitem = new item(name, type, count);
	inventory_pack.push_back(newitem);
}

void inventory::update_inventory(ITEM_TYPE t)
{
	for (auto temp : inventory_pack)
	{
		if (temp->type == t)
		{
			if (temp->count < 1)
			{
				delete_item(t);
			}

		}

	}
}

void inventory::delete_item(ITEM_TYPE type)
{
	int t = 0;
	for (auto temp : inventory_pack)
	{
		t++;
		if (temp->type = type)
		{
			inventory_pack.erase(inventory_pack.begin(), inventory_pack.begin() + t);
		}
	}
}

void inventory::save_config()
{
	std::ofstream config("inventory.cfg", std::ios::out | std::ios::trunc);
	std::string tempo;
	for (auto temp : inventory_pack)
	{
		tempo = "";
		tempo = "[" + GET_TYPES(temp->type) + "]" + "N:" + temp->name + ";" + "C(" + std::to_string(temp->count) + ")~\n";
		config << tempo;
	}
	config.close();
}

inventory inventory::GET_CURRENT_INVENTORY()
{
	return *this;
}

void inventory::drawTexts()
{
	 
	if (current_context!=NULL)
	{
		
		current_context->SetColor(1, 1, 1, 1);
		//Leadwerks::Font* font = Leadwerks::Font::Load("Fonts/apocaliptic.ttf", 20);
		//current_context->SetFont(font);
		for(int i=0; i<inventory_pack.size(); i++)
		{
			current_context->DrawText(std::to_string(inventory_pack.at(i)->count), inventory_pack.at(i)->pos.x, inventory_pack.at(i)->pos.y);
		}
		//current_context->Sync();      
	}
	else
	{
	}
}

void inventory::drawText(std::string text, Leadwerks::Vec2 pos)
{
	if (current_context != NULL)
	{
		current_context->SetColor(0.0, 1.0, 0.2);
		/*Leadwerks::Font* font = Leadwerks::Font::Load("Fonts/apocaliptic.ttf", 25);
		current_context->SetFont(font);
		*/
		
		current_context->SetBlendMode(Leadwerks::Blend::Alpha);
		current_context->DrawText(text, pos.x, pos.y);
		current_context->SetBlendMode(Leadwerks::Blend::Solid);
		//current_context->Sync();      
	}
	else
	{
	}
}


void inventory::drawHUD()
{
	if (current_context != NULL)
	{
		current_context->SetColor(1, 1, 1, 1);
		/*Leadwerks::Font* font = Leadwerks::Font::Load("Fonts/apocaliptic.ttf", 20);
		current_context->SetFont(font);*/
		if (inventory_pack.size() > 0)
		{
			//current_context->DrawText(std::to_string(inventory_pack[0]->count), 714, 515);
		}
		//current_context->Sync();
	}
	else
	{
	}
}