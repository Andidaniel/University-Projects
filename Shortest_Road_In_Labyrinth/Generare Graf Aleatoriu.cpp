#include <SFML/Graphics.hpp>
#include <iostream>
#include "Graph.h"




int main()
{
   	sf::RenderWindow window(sf::VideoMode(800, 800), "LABIRINT");
	window.setFramerateLimit(3);
	Graph g;
	g.Citire();
	sf::Color BackgroundColor(64, 79, 74);
	//g.AfisareListaAdiacenta();
	std::vector<int> De_Colorat = g.DeColorat();
	int index = 0;

	window.clear(BackgroundColor);
	g.Afisare(window);
	window.display();

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}


		if (index < De_Colorat.size())
			g.SetColor(sf::Color::Green, De_Colorat[index++]);
		window.clear(BackgroundColor);
		/// Draw-urile se fac aici
		g.Afisare(window);
		window.display();
		if (index == De_Colorat.size())
		{
			index = 0;
			g.SetInitialColors();
			window.clear(BackgroundColor);
			g.Afisare(window);
			window.display();
		}
		}

    return 0;
}