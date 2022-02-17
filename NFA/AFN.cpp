#include "AFN.h"

void AFN::Citire()
{
	std::ifstream fin("input.txt");
	std::string temporary;
	int nrTemp;
	fin >> nrTemp;
	for (unsigned int i = 0; i < nrTemp; i++)
	{
		fin >> temporary;
		m_stari.insert(temporary);
	}
	fin >> nrTemp;
	for (unsigned int i = 0; i < nrTemp; i++)
	{
		fin >> temporary;
		m_sigma.insert(temporary);
	}
	fin >> nrTemp;
	for (unsigned int i = 0; i < nrTemp; i++)
	{
		Tranzitie t;
		fin >> t;
		m_delta.push_back(t);
	}
	fin >> m_stareInit;

	fin >> nrTemp;
	for (unsigned int i = 0; i < nrTemp; i++)
	{
		fin >> temporary;
		m_stariFin.insert(temporary);
	}
}

void AFN::Afisare()
{
	std::cout << "Multimea starilor: ";
	for (const auto& it : m_stari)
	{
		std::cout << it << ' ';
	}
	std::cout << '\n';
	std::cout << "Multimea simbolurilor: ";
	for (const auto& it : m_sigma)
	{
		std::cout << it << ' ';
	}
	std::cout << '\n';
	std::cout << "Tranzitiile definite pe functia Delta: \n";
	for (unsigned int i = 0; i < m_delta.size(); i++)
	{
		std::cout << m_delta[i];
	}
	std::cout << "Stare initiala: " << m_stareInit << '\n';
	std::cout << "Multimea starilor finale: ";
	for (const auto& it : m_stariFin)
	{
		std::cout << it << ' ';
	}
}

bool AFN::ApartineStari(const std::string& stare)
{
	if (m_stari.find(stare) != m_stari.end())
	{
		return true;
	}
	return false;
}

bool AFN::TranzitieApartineAutomat(const Tranzitie& tranzitie)
{
	if (m_stari.find(tranzitie.stare_init) != m_stari.end())
	{
		if (m_sigma.find(tranzitie.simbol) != m_sigma.end())
		{
			for (int i = 0; i < tranzitie.stari_fin.size(); i++)
			{
				if (m_stari.find(tranzitie.stari_fin[i]) == m_stari.end())
				{
					std::cout << "O stare finala dintr-o tranzitie nu se afla in automat!";
					return false;
				}
			}
			return true;
		}
		else
		{
			std::cout << "Un simbol dintr-o tranzitie nu se afla in automat!";
			return false;
		}
	}
	else {
		std::cout << "O stare initiala dintr-o tranzitie nu se afla in automat!";
		return false;
	}
}

bool AFN::Verificare()
{
	if (ApartineStari(m_stareInit) == false)
	{
		std::cout << "Starea initiala nu apartine starilor automatului!";
		return false;
	}
	for (const auto& it : m_stariFin)
	{
		if (ApartineStari(it) == false)
		{
			std::cout << "Cel putin o stare finala nu apartine starilor automatului!";
			return false;
		}
	}
	for (const auto& it : m_delta)
	{
		if (TranzitieApartineAutomat(it) == false)
			return false;
	}
	return true;
}

bool AFN::accepta(std::string cuvant)
{
	std::string workingString; /// simbolul pe care suntem
	std::unordered_set<std::string> stariCurente; /// starile pe care vom face verificarea
	stariCurente.insert(m_stareInit);   
	std::unordered_set<std::string> stariViitoare; /// starile care vor rezulta si care vor fi mutate in stari curente
	while (cuvant.size())
	{
		workingString.clear();
		workingString.push_back(cuvant[0]);
		cuvant.erase(0, 1);
		bool blocaj = true;
		for (const auto& it : m_delta)
		{
				if (stariCurente.find(it.stare_init)!=stariCurente.end() && it.simbol == workingString)
				{
					blocaj = false;
					for (int j = 0; j < it.stari_fin.size(); j++)
						stariViitoare.insert(it.stari_fin[j]);
				}
		}
		if (blocaj == true)
		{
			std::cout << '\n';
			std::cout << "BLOCAJ";
			return false;
		}
		else {
			stariCurente.clear();
			stariCurente = stariViitoare;
			stariViitoare.clear();
		}
	}
	for (const auto& it : m_stariFin)
	{
		if (stariCurente.find(it) != stariCurente.end())
		{
			std::cout << "\nCUVANT ACCEPTAT";
			return true;
		}
		else
		{
			std::cout << "\nCUVANT RESPINS";
			return false;
		}
		
	}

}
