#include "Nod.h"

Nod::Nod(const float& posX, const float& posY)
{
	m_squareShape.setSize(sf::Vector2f(50.f, 50.f));
	m_posX = posX;
	m_posY = posY;
	m_squareShape.setPosition(sf::Vector2f(m_posX, m_posY));
}
float Nod::get_posX() const
{
	return m_posX;
}
float Nod::get_posY() const
{
	return m_posY;
}
sf::Color Nod::get_color() const
{
	return m_squareShape.getFillColor();
}
void Nod::set_color(sf::Color color)
{
	m_squareShape.setFillColor(color);
	
}

void Nod::draw(sf::RenderWindow& window)
{
	window.draw(m_squareShape);
}
