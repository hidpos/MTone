#pragma once
#include "SFML/Graphics.hpp"
#include <SFML/Config.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
using namespace sf;

class MTuneRenderWindow : public RenderWindow
{
public:
	MTuneRenderWindow(VideoMode mode, const String& title, Uint32 style = Style::Default);
	void InitBackground(const float x, const float y);
	void SetSongName(String name);
	void UpdateStatusPanel(const Music& controller);
	void UpdateControlPanel(Music& controller);
private:
	Font font;
	Color text_color = Color(223, 213, 203);
	Color primary_color = Color(71, 75, 88);
	const int offset = 15;
	const int offset_2 = 20;
	const int offset_el = 10;
	int window_w;
	int window_h;
};