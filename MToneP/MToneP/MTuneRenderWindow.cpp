#include "MTuneRenderWindow.h"

MTuneRenderWindow::MTuneRenderWindow(VideoMode mode, const String& title, Uint32 style, const ContextSettings& settings)
	: RenderWindow(mode, title, style, settings)
{
	Image icon;
	icon.loadFromFile("mtune_logo_panel.png");
	setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
}

void MTuneRenderWindow::InitBackground(const float x, const float y, Color color)
{
	RectangleShape rect(Vector2f(0, 0));
	rect.setFillColor(Color(71, 75, 88));
	rect.setSize(Vector2f(x, y));
}