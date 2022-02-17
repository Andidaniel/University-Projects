#include "Gramatica.h"
#include <fstream>
#include <random>

void Gramatica::Citire_Gramatica()
{
	std::ifstream fin("inputGramatica.txt");
	int nrNTP;
	std::string inString;
	fin >> nrNTP;
	for (int i = 0; i < nrNTP; i++)
	{
		fin >> inString;
		m_Neterminale.insert(inString);
	}
	fin >> nrNTP;
	for (int i = 0; i < nrNTP; i++)
	{
		fin >> inString;
		m_Terminale.insert(inString);
	}
	
	fin >> m_Simbol_Start;
	fin >> nrNTP;
	Productie inProd;
	for (int i = 0; i < nrNTP; i++)
	{
		fin >> inProd;
		m_Productii.push_back(inProd);
	}
	fin.close();
}

void Afisare_Set(const std::unordered_set<std::string>& set)
{
	for (const auto& element : set)
		std::cout << element << ' ';
}

void Gramatica::Afisare_Gramatica() const
{
	std::cout << "Multimea neterminalelor: ";
	Afisare_Set(m_Neterminale);
	std::cout << "\n \nMultimea terminalelor: ";
	Afisare_Set(m_Terminale);
	std::cout << "\n \nSimbol de start: ";
	std::cout << m_Simbol_Start;
	std::cout << "\n \nProductiile: \n";
	for (const auto& productie : m_Productii)
		std::cout << productie<<'\n';
		
}

bool Gramatica::Se_Intersecteaza() const
{

	for (const auto& i_Neterminale : m_Neterminale)
		for (const auto& i_Terminale : m_Terminale)
			if (i_Neterminale == i_Terminale)
			{
				std::cout << "EROARE: MULTIMILE SE INTERSECTEAZA\n";
				return true;
			}
	return false;
}

bool Gramatica::Start_Este_Neterminal() const
{
	for (const auto& i_Neterminal : m_Neterminale)
		if (m_Simbol_Start == i_Neterminal)
			return true;
	return false;
}

bool Gramatica::Contine_Neterminal(const std::string& sir) const
{
	for (const auto& i_Neterminal : m_Neterminale)
		if (sir.find(i_Neterminal) != std::string::npos)
			return true;
	return false;
}

bool Gramatica::Mbr_Stang_Contine_Neterminal() const
{

	for (const auto& i_Productie : m_Productii)
		if (Contine_Neterminal(i_Productie.Get_Stanga()) == false)
			return false;
	return true;

}

bool Gramatica::Productie_Simbol_Start() const
{
	for (const auto& i_Productie : m_Productii)
		if (i_Productie.Get_Stanga() == m_Simbol_Start)
			return true;
	return false;
}

bool Gramatica::Apartine_Neterminale(const std::string& caracter) const
{
	for (const auto& i_Neterminale : m_Neterminale)
		if (caracter == i_Neterminale)
			return true;
	return false;
}

bool Gramatica::Apartine_Terminale(const std::string& caracter) const
{
	for (const auto& i_Terminale : m_Terminale)
		if (caracter == i_Terminale)
			return true;
	return false;
}

bool Gramatica::Productie_Contine_Doar_Elemente_Neterminale_Si_Terminale() const
{
	for (const auto& i_Productie : m_Productii)
	{
		for (int i = 0; i < i_Productie.Get_Stanga().size(); i++)
		{
			std::string litera(1, i_Productie.Get_Stanga()[i]);
			if (Apartine_Neterminale(litera) == false)
				if (Apartine_Terminale(litera) == false)
					return false;
		}

		for (int i = 0; i < i_Productie.Get_Dreapta().size(); i++)
		{
			std::string litera(1, i_Productie.Get_Dreapta()[i]);
			if (Apartine_Neterminale(litera) == false)
				if (Apartine_Terminale(litera) == false)
					return false;
		}

	}
	return true;
}

bool Gramatica::Verificare() const
{
	if (Se_Intersecteaza() == true)
	{
		std::cout << "\n\nTerminalele si Neterminalele se intersecteaza";
		return false;
	}
	if (Start_Este_Neterminal() == false)
	{
		std::cout << "\n\nSimbolul de start nu este neterminal";
		return false;
	}
	if(Mbr_Stang_Contine_Neterminal()==false)
	{
		std::cout << "\n\nExista (cel putin) un membru stang care nu contine niciun neterminal";
		return false;
	}
	if(Productie_Simbol_Start()==false)
	{
		std::cout << "\n\nNu exista nicio productie care contine doar simbolul de start";
		return false;
	}
	if(Productie_Contine_Doar_Elemente_Neterminale_Si_Terminale()==false)
	{
		std::cout << "\n\nExista (cel putin) o productie care contine elemente straine";
		return false;
	}
	//std::cout << "\n\nGramatica este corecta";
	return true;
}

bool Gramatica::Este_Cuvant_Terminal(const std::string& cuv) const
{
	for(const auto& i_Neterminal:m_Neterminale)
		if(cuv.find(i_Neterminal)!=std::string::npos)
			return false;
	return true;
}

std::vector<int> Gramatica::Generare_Pozitii_Aplicabile(const std::string& cuv)
{
	std::vector<int> pozitii;
	for (int i = 0; i < m_Productii.size(); i++)
		if (cuv.find(m_Productii[i].Get_Stanga()) != std::string::npos)
			pozitii.push_back(i);
	return pozitii;
}

int Generare_Numar_Random(int marime) {
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<int> dist(0, marime - 1);
	return dist(rng);
}
void Gramatica::Generare(Optiune optiune)
{


	std::string cuvant = m_Simbol_Start;
	std::string inlocuit;
	std::string inlocuitor;
	std::vector<int> pozitii;
	int pozitie_random;
	pozitii = Generare_Pozitii_Aplicabile(cuvant);
	std::cout << "\n\n Cuvant initial: " << cuvant;
	while (pozitii.size() != 0)
	{
		pozitie_random = Generare_Numar_Random(pozitii.size());
		inlocuit = m_Productii[pozitii[pozitie_random]].Get_Stanga();
		inlocuitor = m_Productii[pozitii[pozitie_random]].Get_Dreapta();
		if (inlocuitor != "L")
			cuvant.replace(cuvant.find(inlocuit), inlocuit.size(), inlocuitor);
		else
			cuvant.erase(cuvant.find(inlocuit), inlocuit.size());
		if (optiune == Optiune::PASI)
			std::cout << "-> R(" << pozitii[pozitie_random] << ") -> " << cuvant;
		pozitii.clear();
		pozitii = Generare_Pozitii_Aplicabile(cuvant);
	}
	if (Este_Cuvant_Terminal(cuvant) == true)
	{
		std::cout << "\n\n Cuvant final: " << cuvant << '\n';
		return;
	}
	
	
}



