#pragma once
#include "SFML/Graphics.hpp"
#include <SFML/Config.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <iostream>
#include <filesystem>
using namespace sf;

class MTuneRenderWindow : public RenderWindow
{
public:
	MTuneRenderWindow(VideoMode mode, const String& title, Uint32 style = Style::Default);
	void InitBackground(const float x, const float y);
	void SetSongName(String name);
	void UpdateStatusPanel(const Music& controller);
	void UpdateControlPanel(const Music& controller);
	void UpdateFilePanel(const Music& controller);
	void ProcessMouseClick(const float Mx, const float My, Music& controller);
	void Update(const Music& controller);
private:
	bool MouseOnButton(const float mx, const float my, Sprite& sprite);
	void TextInit(Text& text, const String info, const Vector2f pos);
	const Color text_color = Color(223, 213, 203);
	const Color primary_color = Color(71, 75, 88);
	const int offset = 15;
	const int offset_2 = 20;
	const int offset_el = 10;
	Sprite pauseS, playS, nextS, prevS, soundOffS, soundOnS;
	Sprite quitS, changeFolderS, changeThemeS;
	RectangleShape soundC_bar_back;
	std::vector<Music> music_queue;
	String current_filePath = "";
	float temp_volume;
	int window_w;
	int window_h;
	Font font;
};