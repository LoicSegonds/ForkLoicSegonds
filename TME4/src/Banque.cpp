#include "Banque.h"

#include <iostream>

using namespace std;

namespace pr {

void Banque::transfert(size_t deb, size_t cred, unsigned int val) {
	//unique_lock<recursive_mutex> g(m);
	Compte & debiteur = comptes[deb];
	Compte & crediteur = comptes[cred];

	if(deb<cred){
		debiteur.lock();
		crediteur.lock();
	}else if(deb>cred){
		crediteur.lock();
		debiteur.lock();
	}else{
		return;
	}

	if (debiteur.debiter(val)) {
		crediteur.crediter(val);
	}
	debiteur.unlock();
	crediteur.unlock();
}
/*Question5:
On a des unique_lock sur debiter et créditer sur le même mutex que le lock, on
se bloque donc une fois, puis on arrive à la fonction débiter qui n'est plus
possible puisque debiteur déjà lock (d'où recursive_mutex).
Question6:
si on ne force pas un ordre on peut avoir un cas où unthread lock débiteur compte1,
puis un autre lock compte2 débiteur, puis les deux essayent de lock leurs créditeurs
qui sont compte2 et compte1 respectivement, donc interbloquage; si on impose de lock
dans l'ordre des indices, cela ne peut pas se produire.
Question9:
les uniquelock sont là pour le comptable, éviter les erreurs. grosse perte de
parallèlisme.
*/


size_t Banque::size() const {
	//unique_lock<recursive_mutex> g(m);
	return comptes.size();
}


bool Banque::comptabiliser (int attendu) const {
	//unique_lock<recursive_mutex> g(m);
	int bilan = 0;
	int id = 0;
	for (const auto & compte : comptes) { //dans l'ordre donc normalement pas d'interlockage

		compte.lock();

		if (compte.getSolde() < 0) {
			cout << "Compte " << id << " en négatif : " << compte.getSolde() << endl;
		}
		bilan += compte.getSolde();
		id++;
	}
	if (bilan != attendu) {
		cout << "Bilan comptable faux : attendu " << attendu << " obtenu : " << bilan << endl;
	}

	for (const auto & compte : comptes) {
		compte.unlock();
	}
	return bilan == attendu;
}
}
