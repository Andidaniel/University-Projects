#pragma once
#include "Productie.h"
#include <vector>
#include <unordered_set>
class Gramatica {
public:
	enum class Optiune {
		CUVANT_FINAL,
		PASI
	};
private:
	std::unordered_set<std::string> m_Neterminale;
	std::unordered_set<std::string> m_Terminale;
	std::string m_Simbol_Start;
	std::vector<Productie> m_Productii;
public:
	Gramatica() = default;
	~Gramatica() = default;
	void Citire_Gramatica();
	void Afisare_Gramatica() const;
	bool Se_Intersecteaza() const; //Prop 1 - ATENTIE: RETURNEZA FALSE DACA NU SE INTERSECTEAZA
	bool Start_Este_Neterminal() const; //Prop 2
	bool Contine_Neterminal(const std::string& sir) const; // Functie ajutatoare pt aceasta \/
	bool Mbr_Stang_Contine_Neterminal() const;//Prop 3 - fiecare membru stang contine cel putin un neterminal
	bool Productie_Simbol_Start() const; // Prop 4 - Exista cel putin o productie care contine in stanga simbolul de start
	bool Apartine_Neterminale(const std::string& caracter) const;
	bool Apartine_Terminale(const std::string& caracter) const; 
	bool Productie_Contine_Doar_Elemente_Neterminale_Si_Terminale() const; // Prop 5 
	bool Verificare() const;
	bool Este_Cuvant_Terminal(const std::string& cuv) const;
	std::vector<int> Generare_Pozitii_Aplicabile(const std::string& cuv);
	void Generare(Optiune optiune);





};