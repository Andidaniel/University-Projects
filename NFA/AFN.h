#pragma once
#pragma once
#include <fstream>
#include <unordered_set>
#include <string>
#include <iostream>
#include <vector>

struct Tranzitie {
	std::string stare_init;
	std::string simbol;
	std::vector<std::string> stari_fin;

	friend std::istream& operator>>(std::istream& is, Tranzitie& t) {
		is >> t.stare_init;
		is >> t.simbol;
		int numarStariFin;
		is >> numarStariFin;
		for (int i = 0; i < numarStariFin; i++)
		{
			std::string temp;
			is >> temp;
			t.stari_fin.push_back(temp);
		}
		return is;
	}
	friend std::ostream& operator<<(std::ostream& os, Tranzitie t) {
		os << '(' << t.stare_init << ',' << t.simbol << ") -> ";
		for (int i = 0; i < t.stari_fin.size(); i++)
			os << t.stari_fin[i] << ' ';
		os << '\n';
			return os;
	}

};

class AFN
{

private:
	std::unordered_set<std::string> m_stari;
	std::unordered_set<std::string> m_sigma;
	std::vector<Tranzitie> m_delta;
	std::string m_stareInit;
	std::unordered_set<std::string> m_stariFin;

public:
	AFN() = default;
	~AFN() = default;
	void Citire();
	void Afisare();
	bool ApartineStari(const std::string& stare);
	bool TranzitieApartineAutomat(const Tranzitie& tranzitie);
	bool Verificare();
	bool accepta(std::string cuvant);

};

