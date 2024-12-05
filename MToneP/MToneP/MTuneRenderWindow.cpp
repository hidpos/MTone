#include "MTuneRenderWindow.h"

MTuneRenderWindow::MTuneRenderWindow(
	VideoMode mode, 
	const String& title, 
	Uint32 style)
	: RenderWindow(mode, title, style)
{
	Image icon;
	icon.loadFromFile("mtune_logo_panel.png");
	setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
	font.loadFromFile("Titania-Regular.ttf");

}

void MTuneRenderWindow::InitBackground(const float x, const float y)
{
	window_w = x;	window_h = y;
	RectangleShape rect, rect_out, rect_out_2, 
		rect_out_3, rect_out_4, rect_out_5;

	{
		rect.setFillColor(primary_color);
		rect_out.setFillColor(primary_color);
		rect_out_2.setFillColor(primary_color);
		rect_out_3.setFillColor(primary_color);
		rect_out_4.setFillColor(primary_color);
		rect_out_5.setFillColor(primary_color);
	}
	{
		rect_out.setOutlineColor(primary_color + Color(10, 10, 10));
		rect_out.setOutlineThickness(2);
		rect_out_2.setOutlineColor(primary_color + Color(10, 10, 10));
		rect_out_2.setOutlineThickness(2);
		rect_out_3.setOutlineColor(primary_color + Color(10, 10, 10));
		rect_out_3.setOutlineThickness(2);
		rect_out_4.setOutlineColor(primary_color + Color(10, 10, 10));
		rect_out_4.setOutlineThickness(2);
		rect_out_5.setOutlineColor(primary_color + Color(10, 10, 10));
		rect_out_5.setOutlineThickness(2);
	}
	{
		rect.setSize(Vector2f(window_w, window_h));
		rect_out.setPosition(offset, offset);
		rect_out.setSize(Vector2f(window_w - offset * 2, window_h - offset * 2));
		rect_out_2.setPosition(offset_2 * 2, offset_2 * 2);
		rect_out_2.setSize(Vector2f(window_w - offset_2 * 4, offset_2 * 5));
		rect_out_3.setPosition(offset_2 * 2, offset_2 * 2 + offset_2 * 6);
		rect_out_3.setSize(Vector2f((window_w - offset_2 * 4) / 1.5, offset_2 * 2));
		rect_out_4.setPosition((window_w - offset_2 * 4) / 1.5 + offset_2 * 5, offset_2 * 2 + offset_2 * 6);
		rect_out_4.setSize(Vector2f((window_w - offset_2 * 4) / 4, offset_2 * 2));
		rect_out_5.setPosition(offset_2 * 2, offset_2 * 11);
		rect_out_5.setSize(Vector2f(window_w - offset_2 * 4, offset_2 * 12));
	}
	
	draw(rect);	 draw(rect_out); draw(rect_out_2); 
	draw(rect_out_3); draw(rect_out_4); draw(rect_out_5);
}

void MTuneRenderWindow::SetSongName(String name)
{
	Text text;
	text.setFont(font);
	text.setString(name);
	text.setCharacterSize(25);
	text.setFillColor(text_color);
	text.setPosition(Vector2f(offset_2 * 2 + offset_el, offset_2 * 2 + offset_el));
	draw(text);
}

void MTuneRenderWindow::UpdateStatusPanel(const Music& controller)
{
	const int bar_offset = controller.getPlayingOffset().asSeconds();
	const int track_duration = controller.getDuration().asSeconds();
	// background bar
	RectangleShape stat_bar_back;
	stat_bar_back.setOutlineColor(text_color);
	stat_bar_back.setOutlineThickness(1);
	stat_bar_back.setPosition(offset_2 * 2.5, offset_2 * 5);
	stat_bar_back.setSize(Vector2f(window_w - offset_2 * 5, offset_2 / 2));
	stat_bar_back.setFillColor(Color(120, 114, 109));
	draw(stat_bar_back);
	// slider
	RectangleShape stat_bar_slider;
	stat_bar_slider.setSize(Vector2f(offset_2 / 2, offset_2 / 2));
	stat_bar_slider.setPosition(offset_2 * 2.5 +
		(stat_bar_back.getSize().x * bar_offset / track_duration),
		offset_2 * 5);
	stat_bar_slider.setFillColor(text_color);
	draw(stat_bar_slider);
	// current playing offset text
	Text text;
	text.setFont(font);
	text.setString(std::to_string(bar_offset) + " / " + std::to_string(track_duration));
	text.setCharacterSize(10);
	text.setFillColor(text_color);
	text.setPosition(Vector2f(offset_2 * 2.5 + window_w - offset_2 * 5 - offset_2 * 3,
		offset_2 * 5 + offset_2 / 2));
	draw(text);
}

void MTuneRenderWindow::UpdateControlPanel(Music& controller)
{
	
}