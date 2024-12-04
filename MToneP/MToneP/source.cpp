#include <iostream>
#include "SFML/Graphics.hpp"
#include "MTuneRenderWindow.h"

using namespace std;
using namespace sf;


int main()
{
	const float window_w = 800;
	const float window_h = 500;
	ContextSettings settings;	settings.antialiasingLevel = 8;
	MTuneRenderWindow window(VideoMode(window_w, window_h), "MTune", Style::Titlebar, settings);


	while (window.isOpen())
	{
		Event e;
		while (window.pollEvent(e))
		{
			if (e.type == Event::Closed) window.close();
		}
		window.clear();

		window.InitBackground(window_w, window_h, Color(71, 75, 88));

		window.display();
	}

	return 0;
}