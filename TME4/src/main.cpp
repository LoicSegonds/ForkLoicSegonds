#include <iostream>
#include "Banque.h"


using namespace std;
using namespace pr;

const int NB_THREAD = 10;
const int NBCOMPTE = 20;
const int SOLDE = 200;

/*Question1:*/
void transaction(Banque& banque){
	for (int i=0; i<1000;++i){
		unsigned int val=rand()%100+1;
		size_t deb=rand()%NBCOMPTE;
		size_t cred=rand()%NBCOMPTE;
		banque.transfert(deb,cred,val);
		this_thread::sleep_for(chrono::milliseconds(rand()%21));
	}
}

int main () {
	vector<thread> threads;
	// TODO : creer des threads qui font ce qui est demandé
	Banque banque(NBCOMPTE,SOLDE);
	threads.reserve(NB_THREAD+1);
	for(int k=0;k<NB_THREAD;++k){
		threads.emplace_back(transaction,ref(banque));
		//ref pour l'envoyer par référence sans ce soucier de si banque est détruit pendant l'utilisation
		//pb compilateur sinon

		if(k==NB_THREAD-1)
			threads.emplace_back(&Banque::comptabiliser,&banque,banque.size()*SOLDE);
		//thread comptable
	}


	for (auto & t : threads) {
		t.join();
	}

	// TODO : tester solde = NB_THREAD * JP
	if(banque.comptabiliser(banque.size()*SOLDE))
		cout<< "Bon solde" << endl;
	return 0;
}


/*Question2:
Non car si les opérations créditer et débiter sont atomiques, le transfert ne
l'est pas, on peut avoir plusieurs débits avant de créditer un compte
Question7:
Non, en effet, si le comptable en est à un compte x, ayant déjà comptabilisé un
compte w et que ce compte fait un transfert vers un compte y non encore comptabilisé
alors le comptable va avoir un montant supérieur au montant attendu puisqu'il aura
compté le compte w non actualisé, et le compte y actualisé.
*/
