#include <iostream>
#include "Gramatica.h"
int main()
{
	Gramatica gramatica;
	gramatica.Citire_Gramatica();
	gramatica.Afisare_Gramatica();

	if (gramatica.Verificare() == false)
		return 0;

	std::cout << "Numar de cuvinte? : ";
	int nr_cuvinte;
	std::cin >> nr_cuvinte;
	for (int i = 0; i < nr_cuvinte; i++)
		gramatica.Generare(Gramatica::Optiune::PASI);

	return 0;
}
