#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <Leadwerks.h>
#include "INV_CONTROLLER.h"
#include "mini_map.h"

enum TYPE_HV {HORIZ, VERTIC};

class line
{
public:
	TYPE_HV type;
	int length;
	int x;
	int y;
};

class sprite
{
public:
	std::string filepath;
	Leadwerks::Texture* sprit;
	int x;
	int y;
};
class text
{
public:
	std::string txt;
	int x;
	int y;
};

class UI_INV
{
	std::vector<line> lines;
	std::vector<sprite> sprites;
	std::vector<text> texts;
	Leadwerks::Context *current_context;
public:
	UI_INV();
	~UI_INV();
	void load_file();
	void parse(std::string string);
	void add_lines(TYPE_HV type, int length, int x, int y);
	void add_images(std::string filepath, int x, int y);
	void add_texts(std::string txt, int x, int y);
	TYPE_HV UI_INV::GET_TYPE(std::string type);
	void drawMENU_UI();
	void drawSprites();
};

