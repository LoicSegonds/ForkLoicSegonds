#include "List.h"
#include <string>
#include <iostream>
#include <cstring>

int main () {

	std::string abc = "abc";
	//FAUTE new char doit contenir \0 donc size=4 et non 3
	char * str = new char [4];
	str[0] = 'a';
	str[1] = 'b';
	str[2] = 'c';
	str[3]='\0';
	//FAUTE size_t est unsigned donc si <0 problème on utilise donc un int
	int i = 0;

	if (! strcmp (str, abc.c_str())) {
		std::cout << "Equal !\n";
	}

	pr::List list;
	list.push_front(abc);
	list.push_front(abc);

	std::cout << "Liste : " << list << std::endl;
	std::cout << "Taille : " << list.size() << std::endl;

	// Affiche à l'envers
	for (i= list.size()-1  ; i >= 0 ; i--) {
		std::cout << "elt " << i << ": " << list[i] << std::endl;
	}
	//FAUTE on peut delete[] sur new char au lieu de faire boucles
	delete[] str;

}
