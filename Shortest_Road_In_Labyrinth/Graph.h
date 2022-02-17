#pragma once
#include "Nod.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <unordered_set>
#include <queue>
#include <stack>
class Graph
{
private:
	int m_lines;
	int m_columns;
	int m_start_node;
	std::vector<int> m_end_nodes;
	std::vector<std::vector<int>> m_graph;
	std::vector<Nod> m_nodes;
	std::vector<sf::Color> m_initial_colors;

public:
	Graph()=default;
	void Citire();
	void Afisare(sf::RenderWindow& window);
	void AfisareListaAdiacenta();
	void SetColor(sf::Color color,int i);
	std::vector<int> BFS(); /// returneaza vectorul de predecesori
	std::vector<int> DeColorat(); /// construieste stiva cu ordinea de afisare pentru nodurile de finish
	void SetInitialColors() ;
};

