#pragma once
#include "SFML/Graphics.hpp"
#include <SFML/Config.hpp>
using namespace sf;

class MTuneRenderWindow : public RenderWindow
{
public:
	MTuneRenderWindow(VideoMode mode, const String& title, Uint32 style = Style::Default, 
		const ContextSettings& settings = ContextSettings());
	void InitBackground(const float x, const float y, Color color);
};