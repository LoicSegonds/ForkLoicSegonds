#include <iostream>
#include <fstream>
#include <regex>
#include <chrono>
#include <vector>


using namespace std;
size_t contient(const string word, vector<string> &vect){
	for(size_t i=0;i<vect.size();++i){
		if(vect[i]==word) return 0;
	}
	vect.push_back(word);
	return 1;
}

void occurences(const string word,vector<pair<string,int>> &vect){
	for(size_t i=0;i<vect.size();++i){
		if(get<0>(vect[i])==word){
			get<1>(vect[i])+=1;
			return;
		}
	}
	vect.push_back(pair<string,int>(word,1));
}




int main () {
	using namespace std;
	using namespace std::chrono;

	ifstream input = ifstream("./WarAndPeace.txt");
	vector<string> vect;
	vector<pair<string,int>> p;

	auto start = steady_clock::now();
	cout << "Parsing War and Peace" << endl;

	size_t nombre_lu = 0;
	size_t nombre_dif=0;

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
		nombre_dif+=contient(word,vect);
		nombre_lu++;
	}
	input.close();

	cout << "Finished Parsing War and Peace" << endl;

	auto end = steady_clock::now();
    cout << "Parsing took "
              << duration_cast<milliseconds>(end - start).count()
              << "ms.\n";

    cout << "Found a total of " << nombre_lu << " words." << endl;
		cout << "Found a total of " << nombre_dif << " different words." << endl;
		for(size_t i=0;i<p.size();++i){
			string a=get<0>(p[i]);
			if(a=="war" || a=="peace")
				cout << "Found a total of " << get<1>(p[i]) << " "<<a << endl;
		}
		/*complexité quadratique*/
    return 0;
}


/*Question 1 il y a 566193 mots en à peu près 2 sec*/
