#include <iostream>
#include "AFN.h"

int main()
{
    AFN Automat;
    Automat.Citire();
   
	if (Automat.Verificare())
	{
		Automat.Afisare();
		std::cout << '\n';
		std::string cuvant;
		std::cout << "\nIntroduceti cuvantul: ";
		std::cin >> cuvant;
		Automat.accepta(cuvant);
		while (true)
		{
			std::cout << "\nDaca doriti sa continuati introduceti un cuvant, daca nu, introduceti STOP\n";
			std::cin >> cuvant;
			if (cuvant == "STOP")
				break;
			else
				Automat.accepta(cuvant);
		}

	}
}

