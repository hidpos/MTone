#include "SFML/Graphics.hpp"
#include "MTuneRenderWindow.h"

using namespace sf;

const float window_w = 800;
const float window_h = 500;

int main()
{
	MTuneRenderWindow window(VideoMode(window_w, window_h), "MTune", Style::Close);
	
	while (window.isOpen())
	{
		Event e;
		while (window.pollEvent(e))
		{
			const float Mx = Mouse::getPosition(window).x;
			const float My = Mouse::getPosition(window).y;
			if (e.type == Event::Closed) 
				window.close(); 
			if (e.type == Event::MouseButtonPressed)
				window.ProcessMouseClick(Mx, My);
		}
		window.clear();

		window.InitBackground(window_w, window_h);
		window.Update();

		window.display();
	}

	return 0;
}