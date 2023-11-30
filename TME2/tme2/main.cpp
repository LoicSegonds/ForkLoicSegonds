#include <iostream>
#include <fstream>
#include <regex>
#include <chrono>
#include <vector>
#include "Hashmap.h"


using namespace std;
using namespace par;
/*size_t contient(const string word, vector<string> &vect){
	for(size_t i=0;i<vect.size();++i){
		if(vect[i]==word) return 0;
	}
	vect.push_back(word);
	return 1;
}*/

void occurences(const string word,vector<pair<string,int>> &vect){
	for(size_t i=0;i<vect.size();++i){
		if(get<0>(vect[i])==word){
			get<1>(vect[i])+=1;
			return;
		}
	}
	vect.push_back(pair<string,int>(word,1));
}

void occurences2(const string word,Hashtable<string,int> &hash){
	int *a;
	if((a=hash.get(word))!=nullptr){
		hash.put(word,*a+1);
	}else{
		hash.put(word,1);
	}
}




int main () {
	using namespace std;
	using namespace std::chrono;

	ifstream input = ifstream("./WarAndPeace.txt");
	vector<string> vect;
	vector<pair<string,int>> p;
	Hashtable<string,int> hash(27);

	auto start = steady_clock::now();
	cout << "Parsing War and Peace" << endl;

	size_t nombre_lu = 0;
	//size_t nombre_dif=0;

	// prochain mot lu
	string word;
	// une regex qui reconnait les caractères anormaux (négation des lettres)
	regex re( R"([^a-zA-Z])");
	while (input >> word) {
		// élimine la ponctuation et les caractères spéciaux
		word = regex_replace ( word, re, "");
		// passe en lowercase
		transform(word.begin(),word.end(),word.begin(),::tolower);
		// word est maintenant "tout propre"

		if (nombre_lu % 100 == 0)
			// on affiche un mot "propre" sur 100
			cout << nombre_lu << ": "<< word << endl;
		//nombre_dif+=contient(word,vect);
		nombre_lu++;
		//occurences(word,p);
		occurences2(word,hash);
	}
	input.close();

	cout << "Finished Parsing War and Peace" << endl;

	auto end = steady_clock::now();
    cout << "Parsing took "
              << duration_cast<milliseconds>(end - start).count()
              << "ms.\n";

    cout << "Found a total of " << nombre_lu << " words." << endl;
		//cout << "Found a total of " << nombre_dif << " different words." << endl;
		//cout << "Found a total of " << p.size() << " different words." << endl;
		cout << "Found a total of " << hash.size() << " different words." << endl;
		/*complexité quadratique*/
		/*
		int war=0;
		int peace=0;
		int toto=0;
		for(size_t i=0;i<p.size();++i){
			string a=get<0>(p[i]);
			if(a=="war")
				war=get<1>(p[i]);
			if(a=="peace")
				peace=get<1>(p[i]);
			if(a=="toto")
				toto=get<1>(p[i]);
		}
		cout << "Found a total of " << war << " war." << endl;
		cout << "Found a total of " << peace << " peace." << endl;
		cout << "Found a total of " << toto << " toto." << endl;
		*/
		int *war;
		if((war=hash.get("war"))!=nullptr){
			cout << "Found a total of " << *war << " war." << endl;
		}
		int *peace;
		if((peace=hash.get("peace"))!=nullptr){
			cout << "Found a total of " << *peace << " peace." << endl;
		}
		int *toto;
		if((toto=hash.get("toto"))!=nullptr){
			cout << "Found a total of " << *toto << " toto." << endl;
		}else{
			cout << "Found a total of 0 toto." << endl;
		}

		//Question 7

		//On fait comme ça du a des problèmes de conversion de type du compilateur
		//c'est pour ça qu'on a rajouté un opérateur à Entry pour pouvoir push push_back
		//conversion de Entry vers pair<string,int>
		vector<pair<string, int>> vectorcopy;
		Hashtable<string,int>::iterator k=hash.begin();
		Hashtable<string,int>::iterator e=hash.end();

		while(k!=e){
			vectorcopy.push_back(*k);
			++k;
		}

		//Question 8
		sort(vectorcopy.begin(), vectorcopy.end(),[](const auto& a, const auto& b){
        return a.second>b.second;
    }
		);

    std::cout << "Les dix mots les plus fréquents :" << std::endl;
    for (size_t i = 0; i < 10; ++i) {
        cout << vectorcopy[i].first<<": "<< vectorcopy[i].second<<" occurrences"<< std::endl;
    }
    return 0;
}


/*Question 1 il y a 566193 mots en à peu près 2 sec*/
