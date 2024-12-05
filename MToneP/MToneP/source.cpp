#include <iostream>
#include "SFML/Graphics.hpp"
#include "MTuneRenderWindow.h"

using namespace std;
using namespace sf;

const float window_w = 800;
const float window_h = 500;

int main()
{
	MTuneRenderWindow window(VideoMode(window_w, window_h), "MTune", Style::Close);
	Music music_controller;
	music_controller.openFromFile("FOVLA - CRUSHER.mp3");
	music_controller.play();
	
	while (window.isOpen())
	{
		Event e;
		while (window.pollEvent(e))
		{
			if (e.type == Event::Closed) window.close();
		}
		window.clear();

		window.InitBackground(window_w, window_h);
		window.SetSongName("FOVLA - CRUSHER");
		window.UpdateStatusPanel(music_controller);
		window.UpdateControlPanel(music_controller);

		window.display();
	}

	return 0;
}