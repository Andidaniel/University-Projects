#pragma once
#include <string>
#include <iostream>

class Productie {
private:
	std::string m_Parametru_Stanga;
	std::string m_Parametru_Dreapta;
public:
	Productie() = default;
	~Productie() = default;

	std::string Get_Stanga() const;
	std::string Get_Dreapta() const;
	
	friend std::istream& operator>>(std::istream& in, Productie& prod);
	friend std::ostream& operator<<(std::ostream& os, const Productie& prod);


};