#include "MTuneRenderWindow.h"

MTuneRenderWindow::MTuneRenderWindow(VideoMode mode, const String& title, Uint32 style)
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
	stat_bar_slider.setSize(Vector2f(stat_bar_back.getSize().x * bar_offset / track_duration, offset_2 / 2));
	stat_bar_slider.setPosition(offset_2 * 2.5,
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

void MTuneRenderWindow::UpdateControlPanel(const Music& controller)
{
	// background bar
	soundC_bar_back.setOutlineColor(text_color);
	soundC_bar_back.setOutlineThickness(1);
	soundC_bar_back.setPosition((window_w - offset_2 * 4) / 1.5 + offset_2 * 7, offset_2 * 2 + offset_2 * 6.75);
	soundC_bar_back.setSize(Vector2f((window_w - offset_2 * 4) / 5.5, offset_2 / 2));
	soundC_bar_back.setFillColor(Color(120, 114, 109));
	draw(soundC_bar_back);
	// slider
	RectangleShape soundC_slider;
	soundC_slider.setSize(Vector2f(offset_2 / 2, offset_2 / 2));
	soundC_slider.setPosition(((window_w - offset_2 * 4) / 1.5 + offset_2 * 6.5) +
		(soundC_bar_back.getSize().x * controller.getVolume() / 100),
		offset_2 * 2 + offset_2 * 6.75);
	soundC_slider.setFillColor(text_color);
	draw(soundC_slider);
	// volume text
	Text text;
	text.setFont(font);
	const int volume = controller.getVolume();
	text.setString(std::to_string(volume));
	text.setCharacterSize(13);
	text.setFillColor(text_color);
	text.setPosition((window_w - offset_2 * 4) / 1.5 + offset_2 * 5.5, 
		offset_2 * 2 + offset_2 * 6.5);
	draw(text);

	// main control panel
	Texture pauseT, playT, nextT, prevT, soundOffT, soundOnT;
	{
		pauseT.loadFromFile("pause.png");
		playT.loadFromFile("play.png");
		nextT.loadFromFile("nextTrack.png");
		prevT.loadFromFile("prevTrack.png");
		soundOffT.loadFromFile("soundOff.png");
		soundOnT.loadFromFile("SoundOn.png");

		nextS.setTexture(nextT);
		nextS.setScale(Vector2f(0.4, 0.4));
		nextS.setPosition(Vector2f((offset_2 * 2 + (window_w - offset_2 * 4) / 1.5) / 4 * 2.6,
			offset_2 * 2 + offset_2 * 5.8));

		prevS.setTexture(prevT);
		prevS.setScale(Vector2f(0.4, 0.4));
		prevS.setPosition(Vector2f((offset_2 * 2 + (window_w - offset_2 * 4) / 1.5) / 3,
			offset_2 * 2 + offset_2 * 5.8));
	}
	if (controller.getStatus() == SoundSource::Status::Playing)
	{
		pauseS.setTexture(pauseT);
		pauseS.setScale(Vector2f(0.4, 0.4));
		pauseS.setPosition(Vector2f((offset_2 * 2 + (window_w - offset_2 * 4) / 1.5) / 2,
			offset_2 * 2 + offset_2 * 5.8));
		playS.setPosition(Vector2f(-100, -100));
		draw(pauseS);
	}
	else
	{
		playS.setTexture(playT);
		playS.setScale(Vector2f(0.4, 0.4));
		playS.setPosition(Vector2f((offset_2 * 2 + (window_w - offset_2 * 4) / 1.5) / 2,
			offset_2 * 2 + offset_2 * 5.8));
		pauseS.setPosition(Vector2f(-100, -100));
		draw(playS);
	}
	if (controller.getVolume() == 0)
	{
		soundOnS.setTexture(soundOnT);
		soundOnS.setScale(Vector2f(0.115, 0.115));
		soundOnS.setPosition(Vector2f((offset_2 * 2 + (window_w - offset_2 * 4) / 1.5) / 5.5,
			offset_2 * 2 + offset_2 * 6.3));
		soundOffS.setPosition(Vector2f(-100, -100));
	}
	else
	{
		soundOffS.setTexture(soundOffT);
		soundOffS.setScale(Vector2f(0.1, 0.1));
		soundOffS.setPosition(Vector2f((offset_2 * 2 + (window_w - offset_2 * 4) / 1.5) / 5.5,
			offset_2 * 2 + offset_2 * 6.3));
		soundOnS.setPosition(Vector2f(-100, -100));
	}
	draw(nextS); draw(prevS);
	draw(soundOffS); draw(soundOnS);
}

void MTuneRenderWindow::UpdateFilePanel(const Music& controller)
{
	// settings text
	Text text, text_2, text_3, text_4, folder_path;
	TextInit(text, "Change music folder", Vector2f(offset_2 * 3, offset_2 * 17));
	TextInit(text_2, "Change client theme", Vector2f(offset_2 * 3, offset_2 * 19));
	TextInit(text_3, "Quit client", Vector2f(offset_2 * 3, offset_2 * 21));
	TextInit(text_4, "Current folder:", Vector2f(offset_2 * 3, offset_2 * 12));
	TextInit(folder_path, current_filePath, Vector2f(offset_2 * 3, offset_2 * 13.5));
	Texture t1, t2, t3;
	t1.loadFromFile("open_arrow.png");
	t2.loadFromFile("open_arrow.png");
	t3.loadFromFile("open_arrow.png");
	changeFolderS.setTexture(t1);
	changeThemeS.setTexture(t2);
	quitS.setTexture(t3);

	changeFolderS.setScale(Vector2f(0.2, 0.2));
	changeFolderS.setPosition(Vector2f(offset_2 * 35, offset_2 * 17));

	changeThemeS.setScale(Vector2f(0.2, 0.2));
	changeThemeS.setPosition(Vector2f(offset_2 * 35, offset_2 * 19));

	quitS.setScale(Vector2f(0.2, 0.2));
	quitS.setPosition(Vector2f(offset_2 * 35, offset_2 * 21));

	draw(changeFolderS);
	draw(quitS);
	draw(changeThemeS);
}

void MTuneRenderWindow::ProcessMouseClick(const float Mx, const float My, Music& controller)
{
	if (Mx > soundC_bar_back.getPosition().x + 10 && Mx < soundC_bar_back.getPosition().x + soundC_bar_back.getSize().x && My > soundC_bar_back.getPosition().y && My < soundC_bar_back.getPosition().y + soundC_bar_back.getSize().y)
		controller.setVolume((Mx - soundC_bar_back.getPosition().x) * 100 / soundC_bar_back.getSize().x);
	if (MouseOnButton(Mx, My, pauseS))
		controller.pause();
	if (MouseOnButton(Mx, My, playS))
		controller.play();
	if (MouseOnButton(Mx, My, soundOffS))
	{
		temp_volume = controller.getVolume();
		controller.setVolume(0);
	}
	if (MouseOnButton(Mx, My, soundOnS) && controller.getVolume() == 0)
		controller.setVolume(temp_volume);
	if (MouseOnButton(Mx, My, quitS))
		close();
}

void MTuneRenderWindow::Update(const Music& controller)
{
	UpdateControlPanel(controller);	UpdateStatusPanel(controller); UpdateFilePanel(controller);
}

bool MTuneRenderWindow::MouseOnButton(const float mx, const float my, Sprite& sprite)
{
	if (mx > sprite.getPosition().x &&
		mx < sprite.getPosition().x + 50 &&
		my > sprite.getPosition().y &&
		my < sprite.getPosition().y + 50)
		return true;
	else return false;
}

void MTuneRenderWindow::TextInit(Text& text, const String info, const Vector2f pos)
{
	text.setFont(font);
	text.setString(info);
	text.setCharacterSize(16);
	text.setFillColor(text_color);
	text.setPosition(pos);
	draw(text);
}