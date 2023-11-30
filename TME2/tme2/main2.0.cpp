#include <iostream>
#include <fstream>
#include <regex>
#include <chrono>
#include <vector>
#include <unordered_map>
#include <forward_list>


using namespace std;
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

void occurences2(const string word,unordered_map<string,int> &hash){
	auto a= hash.find(word);
	if(a!=hash.end())
		a->second++;
	else
		hash.insert(make_pair(word,1));
}



//inverser la table
unordered_map<int,forward_list<string>> inverserTable(const unordered_map<string,int>&hash){

		unordered_map<int,forward_list<string>>newHash;

    // Itération sur la table actuelle
		for(auto a=hash.begin();a!=hash.end();){
			auto paire=*a;
			int val=paire.second;
			string word=paire.first;

			auto b= newHash.find(val);
			if(b!=newHash.end()){
				(b->second).push_front(word);
			}else{
				forward_list<string> liste;
				liste.push_front(word);
				newHash.insert(make_pair(val,liste));
			}
			++a;
		}
    return newHash;
}



// Fonction pour afficher les mots ayant un nombre spécifié d'occurrences
void afficherOccurrence(const unordered_map<int,forward_list<string>>&hash,int N){
    auto it=hash.find(N);

    if(it!=hash.end()){
        cout<<"Mots avec "<<it->first<<" occurrences : "<<endl;
        for (const string & word : it->second) {
            cout<< word<<endl;
        }
    }else{
        cout<<"Aucun mot avec "<<N<<" occurrences."<<endl;
    }
}





int main () {
	using namespace std;
	using namespace std::chrono;

	ifstream input = ifstream("./WarAndPeace.txt");
	vector<string> vect;
	vector<pair<string,int>> p;
	unordered_map<string,int> hash(27);

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


		auto war=hash.find("war");
		if( war != hash.end()){
			cout << "Found a total of " << (*war).second<< " war." << endl;
		}
		auto peace=hash.find("peace");
		if(peace != hash.end()){
			cout << "Found a total of " << (*peace).second << " peace." << endl;
		}
		auto toto=hash.find("toto");
		if(toto != hash.end()){
			cout << "Found a total of " << (*toto).second << " toto." << endl;
		}else{
			cout << "Found a total of 0 toto." << endl;
		}

		//Question 7
		vector<pair<string, int>> vectorcopy(hash.begin(),hash.end());

		//Question 8
		sort(vectorcopy.begin(), vectorcopy.end(),[](const auto& a, const auto& b){
        return a.second>b.second;
    }
		);

    std::cout << "Les dix mots les plus fréquents :" << std::endl;
    for (size_t i = 0; i < 10; ++i) {
        cout << vectorcopy[i].first<<": "<< vectorcopy[i].second<<" occurrences"<< std::endl;
    }


		unordered_map<int,forward_list<string>> inverse=inverserTable(hash);
		afficherOccurrence(inverse,161);
		//Question 9
		//deux unordered_map; une pour chaque paramètre qui nous intéresse

    return 0;
}


/*Question 1 il y a 566193 mots en à peu près 2 sec*/
