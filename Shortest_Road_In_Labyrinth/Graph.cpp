#include "Graph.h"

void Graph::Citire()
{
	std::ifstream fin("labirint.txt");
	
	fin >> m_lines >> m_columns;

	std::vector<std::vector<int>> matrix;
	matrix.resize(m_lines);
	for (int i = 0; i < m_lines; ++i)
	{
		for (int j = 0; j < m_columns; ++j)
		{
			int element;
			fin >> element;
			matrix[i].push_back(element);
		}
	}
	const float unit = 700 / std::max(m_columns,m_lines);
	
	const int line_index[4] = {-1,0,0,1};
	const int column_index[4] = {0,-1,1,0};

	for (int i = 0; i < m_lines; ++i)
		for (int j = 0; j < m_columns; ++j)
		{
			Nod new_nod((j+1)*unit,(i+1)*unit);
			switch (matrix[i][j])	
			{
			case 0:
				new_nod.set_color(sf::Color::Black);
				break;
			case 1:
				new_nod.set_color(sf::Color::White);
				break;
			case 2:
				new_nod.set_color(sf::Color::Red);
				m_end_nodes.push_back(m_nodes.size());
				break;
			case 3:
				new_nod.set_color(sf::Color::Blue);
				m_start_node = m_nodes.size();
				break;
			default:
				break;
			}
			m_nodes.push_back(new_nod);
			m_initial_colors.push_back(new_nod.get_color());
			m_graph.resize(m_lines * m_columns);

			for (int k = 0; k < 4; k++)
			{
				if (matrix[i][j] == 0)
					continue;
				if (i + line_index[k] >= 0 && i + line_index[k] < m_lines &&
					j + column_index[k] >= 0 && j + column_index[k] < m_columns)
					if (matrix[i + line_index[k]][j + column_index[k]] != 0)
						m_graph[i * m_columns + j].push_back((i+ line_index[k])*m_columns + (j+ column_index[k]));
						
			}
		
		}

}

void Graph::Afisare(sf::RenderWindow& window)
{
	for (int i = 0; i < m_nodes.size(); i++)
	{
		m_nodes[i].draw(window);
	}
}

void Graph::AfisareListaAdiacenta()
{
	//for (int i = 0; i < m_graph.size(); i++)
	//{
	//	std::cout << '\n';
	//	std::cout << "Nodul " << i << ": ";
	//	for (int j = 0; j < m_graph[i].size(); j++)
	//		std::cout << m_graph[i][j] << ' ';
	//}
	//
	//std::cout <<"\n Nod de start: "<< m_start_node;
	//std::cout << "\n Noduri de iesire: ";

	//for (int i = 0; i < m_end_nodes.size(); i++)
	//	std::cout << m_end_nodes[i] << ' ';


	/*std::vector<int> predecesori = BFS();
	for (int i = 0; i < predecesori.size(); i++)
	{
		std::cout << i << ": ";
		std::cout << predecesori[i] << '\n';
	}*/

	std::vector<int> testColorat = DeColorat();
	for (int i = 0; i < testColorat.size(); i++)
		std::cout << testColorat[i] << ' ';

}

void Graph::SetColor(sf::Color color, int i)
{
	m_nodes[i].set_color(color);
}

std::vector<int> Graph::BFS()
{
	std::vector<int> predecesors;
	predecesors.resize(m_nodes.size());
	std::queue<int> bfs_queue;
	bool* visited = new bool[m_nodes.size()];
	for (int i = 0; i < m_nodes.size(); i++)
		visited[i] = false;
	bfs_queue.push(m_start_node);
	visited[m_start_node] = true;
	while (!bfs_queue.empty())
	{
		for (int i = 0; i < m_graph[bfs_queue.front()].size(); i++)
		{
			if (visited[m_graph[bfs_queue.front()][i]] == false)
			{
				bfs_queue.push(m_graph[bfs_queue.front()][i]);
				predecesors[m_graph[bfs_queue.front()][i]] = bfs_queue.front();
				visited[m_graph[bfs_queue.front()][i]] = true;
			}
		}
		bfs_queue.pop();
	}

	return predecesors;
}

std::vector<int> Graph::DeColorat()
{
	std::vector<int> predecesori = BFS();
	std::stack<int> toBeColoured;
	for (int i = 0; i < m_end_nodes.size(); i++)
	{
		int temporaryNode = m_end_nodes[i];
		while (predecesori[temporaryNode] != 0)
		{
			toBeColoured.push(temporaryNode);
			temporaryNode = predecesori[temporaryNode];
		}
	}
	std::vector<int> to_be_coloured;
	while (!toBeColoured.empty())
	{
		bool exists = false;
		for (int i = 0; i < to_be_coloured.size() && exists == false; i++)
			if (toBeColoured.top() == to_be_coloured[i])
				exists = true;
		if (exists == false)
		{
			to_be_coloured.push_back(toBeColoured.top());
		}
		toBeColoured.pop();

	}

	return to_be_coloured;
}

void Graph::SetInitialColors()
{
	for (int i = 0; i < m_nodes.size(); i++)
	{
		m_nodes[i].set_color(m_initial_colors[i]);
	}
}


