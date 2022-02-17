#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Nod
{

private:
	float m_posX;
	float m_posY;
	sf::RectangleShape m_squareShape;


public:
	Nod(const float& posX, const float& posY); // constructor cu parametrii x,y pe ecran ai nodului
	float get_posX() const; // getter pt pozitia x, pentru functia de desenare mai tarziu
	float get_posY() const; // getter pt pozitia y, pentru functia de desenare mai tarziu
	sf::Color get_color() const; //getter pt color
	void set_color(sf::Color color);
	void draw(sf::RenderWindow& window);


};

