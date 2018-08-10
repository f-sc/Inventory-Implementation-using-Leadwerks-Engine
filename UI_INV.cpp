#include "UI_INV.h"



UI_INV::UI_INV()
{
}


UI_INV::~UI_INV()
{
}

void UI_INV::load_file()
{
	std::string temp;
	std::ifstream config("UI.cfg");
	if (config.is_open())
	{
		while (getline(config, temp))
		{
			parse(temp);
		}
	}
	else {
		std::cout << "Error loading config!";
	}
}

TYPE_HV UI_INV::GET_TYPE(std::string type)
{
	if (type == "HORISONT")
	{
		return HORIZ;
	}
	else
	{
		return VERTIC;
	}


}

void UI_INV::parse(std::string string)
{
	std::string HV;
	std::string LENGTH;
	std::string COORD;
	std::string temp_t;
	std::string tempo_t;
	int count = 0;
	int temp = 0;
	int x, y;
	if (string[temp] == '[')
	{
		temp++;
		while (string[temp] != ']')
		{

			HV += string[temp];
			//HV[temp + 1] = ']';
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
					LENGTH += string[temp];
					temp++;
				}
			}
			
			if (string[temp] == '(')
			{
				temp++;
				
				while (string[temp] != '&')
				{
					std::cout << string[temp] << "\n";

						tempo_t += string[temp];
						temp++;
				}
				temp++;
				while (string[temp] != ')')
				{
					temp_t += string[temp];
					temp++;
				}
				
			}
			//value += string[temp];
		}

	}
	if ((HV=="HORISONT") || (HV == "VERTICAL"))
	{
		add_lines(GET_TYPE(HV), stoi(LENGTH), stoi(tempo_t), stoi(temp_t));
	}
	else if(HV=="IMAGE")
	{
		add_images((LENGTH+".tex"), stoi(tempo_t), stoi(temp_t));
	}
	else if(HV=="TEXT")
	{
		std::cout << "Text added!\n";
		add_texts(LENGTH, stoi(tempo_t), stoi(temp_t));
	}
	//drawMENU_UI();
}

void UI_INV::add_lines(TYPE_HV type, int length, int x, int y)
{
	line newline;
	newline.type = type;
	newline.length = length;
	newline.x = x;
	newline.y = y;
	lines.push_back(newline);
}

void UI_INV::add_images(std::string filepath, int x, int y)
{
	sprite newsprite;
	newsprite.filepath = filepath;
	newsprite.x = x;
	newsprite.y = y;
	sprites.push_back(newsprite);
}

void UI_INV::add_texts(std::string txt, int x, int y)
{
	text newtext;
	newtext.txt = txt;
	newtext.x = x;
	newtext.y = y;
	texts.push_back(newtext);
}

void UI_INV::drawMENU_UI()
{
	current_context = Leadwerks::Context::GetCurrent();
	//current_context->Clear();

	for (auto temp : lines)
	{
		current_context->SetColor(1, 1, 1, 1);
		if (temp.type == HORIZ)
		{
			current_context->DrawLine(temp.x, temp.y, (temp.x + temp.length), temp.y);
		}
		else if(temp.type == VERTIC)
		{
			current_context->DrawLine(temp.x, temp.y, temp.x, (temp.y+temp.length));
		}
	}
	current_context->Sync();
}

void UI_INV::drawSprites()
{
	for (auto temp : sprites)
	{
		temp.sprit = Leadwerks::Texture::Load("Materials/HUD/inventory/"+temp.filepath);
		if (temp.sprit)
		{
			current_context->SetBlendMode(Leadwerks::Blend::Alpha);
			current_context->DrawImage(temp.sprit, temp.x, temp.y);
		}
		else
		{
			std::cout << "\nUnable to load texture!\n";
		}
	}
	current_context->Sync();
}


