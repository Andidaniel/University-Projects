#include "Productie.h"


std::string Productie::Get_Dreapta() const
{
	return m_Parametru_Dreapta;
}

std::string Productie::Get_Stanga() const
{
	return m_Parametru_Stanga;
}

std::istream& operator>>(std::istream& in, Productie& prod) {
	in >> prod.m_Parametru_Stanga >> prod.m_Parametru_Dreapta;
	return in;
}

std::ostream& operator<<(std::ostream& os, const Productie& prod)
{
	os << prod.m_Parametru_Stanga << " -> " << prod.m_Parametru_Dreapta;
	return os;
}

