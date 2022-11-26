#include <iostream>
#include <SFML/Graphics.hpp>

void initWin(
	sf::RenderWindow& window, std::string title, unsigned int width, unsigned int height,
	unsigned int antiAliasing = 4, unsigned int frameLimit = 60
);
void initFpsMetter(sf::Text& fps, sf::Font& font, unsigned int width);

int main(char* args[])
{
	// font (verdana)
	sf::Font verdana;
	if (!verdana.loadFromFile("verdana.ttf")) return -1;

	unsigned int width = 1280, height = 720;
	sf::RenderWindow window;
	initWin(window, "Game", width, height);

	// performace measurement
	sf::Text fps;
	initFpsMetter(fps, verdana, width);

	// game loop
	sf::Clock clock;
	while (window.isOpen())
	{
		// handle events
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::KeyPressed:
				switch (event.key.code)
				{
				case sf::Keyboard::Key::Escape:
					window.close();
					break;
				}
			}
		}

		// update scene

		sf::Time dt = clock.restart();
		fps.setString(std::to_string(int(1/dt.asSeconds())));

		// render
		window.clear(); // Black by default
		window.draw(fps);

		// draw 
		window.display();		
	}

	return 0;
}


void initWin(
	sf::RenderWindow& window, std::string title, unsigned int width, unsigned int height,
	unsigned int antiAliasing, unsigned int frameLimit
)
{
	sf::ContextSettings context(
		0, 0,
		antiAliasing, // anti aliasing
		1, 1, sf::ContextSettings::Attribute::Default, false
	);
	window.create(
		sf::VideoMode(width, height),
		title,
		sf::Style::Titlebar | sf::Style::Close,
		context
	);
	window.setFramerateLimit(frameLimit);

	std::cout << title << " is running...";
}

void initFpsMetter(sf::Text& fps, sf::Font& font, unsigned int width)
{
	fps.setFont(font);
	fps.setPosition(sf::Vector2f(width - 80.0f, 0));
	fps.setOutlineThickness(1);
	fps.setFillColor(sf::Color::White);
	fps.setOutlineColor(sf::Color::Black);

	fps.setString("--");
}