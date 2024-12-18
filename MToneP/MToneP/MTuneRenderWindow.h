#pragma once
#include "SFML/Graphics.hpp"
#include <SFML/Config.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <iostream>
#include <string>
#include <windows.h>
#include <algorithm>
#include <filesystem>
using namespace sf;
namespace fs = std::filesystem;

class MTuneRenderWindow : public RenderWindow
{
public:
	MTuneRenderWindow(VideoMode mode, const String& title, Uint32 style = Style::Default);
	void InitBackground(const float x, const float y);
	void SetSongName(String name);
	void UpdateStatusPanel();
	void UpdateControlPanel();
	void UpdateFilePanel();
	void ProcessMouseClick(const float Mx, const float My);
	void Update();
private:
	void LoadMusicVector(std::string path);
	bool MouseOnButton(const float mx, const float my, Sprite& sprite);
	void TextInit(Text& text, const String info, const Vector2f pos);
	Color text_color = Color(223, 213, 203);
	Color primary_color = Color(71, 75, 88);
	const int offset = 15;
	const int offset_2 = 20;
	const int offset_el = 10;
	Sprite pauseS, playS, nextS, prevS, soundOffS, soundOnS;
	Sprite quitS, changeFolderS, changeThemeS;
	RectangleShape soundC_bar_back;
	std::vector<String> music_queue;
	Music controller;
	String current_filePath = "D:/music/";
	bool order_changed = false;
	int current_track = 0;
	float temp_volume;
	int window_w;
	int window_h;
	Font font;
};