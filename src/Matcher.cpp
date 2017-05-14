#include "Matcher.h"


void pre_kmp(string pattern, vector<int> & prefix){
	int m=pattern.length();
	prefix[0]=-1;
	int k=-1;
	for (int q=1; q<m; q++) {
		while (k>-1 && pattern[k+1]!=pattern[q])
			k = prefix[k];
		if (pattern[k+1]==pattern[q]) k=k+1;
		prefix[q]=k;
	}
}

int kmp(string text, string pattern){
	int num=0;
	int m=pattern.length();
	vector<int> prefix(m);
	pre_kmp(pattern, prefix);

	int n=text.length();

	int q=-1;
	for (int i=0; i<n; i++) {
		while (q>-1 && pattern[q+1]!=text[i])
			q=prefix[q];
		if (pattern[q+1]==text[i])
			q++;
		if (q==m-1) {
			num++;
			q=prefix[q];
		}
	}
	return num;
}

int damerau_levenshtein_distance(string p_string1, string p_string2){

	int l_string_length1 = p_string1.length();
	int l_string_length2 = p_string2.length();
	int d[l_string_length1+1][l_string_length2+1];

	int i;
	int j;
	int l_cost;

	for (i = 0;i <= l_string_length1;i++){
		d[i][0] = i;
	}
	for(j = 0; j<= l_string_length2; j++){
		d[0][j] = j;
	}
	for (i = 1;i <= l_string_length1;i++){
		for(j = 1; j<= l_string_length2; j++){
			if( p_string1[i-1] == p_string2[j-1] ){
				l_cost = 0;
			}
			else{
				l_cost = 1;
			}
			d[i][j] = min(d[i-1][j] + 1,            // delete
					min(d[i][j-1] + 1,         		// insert
							d[i-1][j-1] + l_cost));   		// substitution

			if((i > 1) && (j > 1) &&
					(p_string1[i-1] == p_string2[j-2]) &&
					(p_string1[i-2] = p_string2[j-1])){
				d[i][j] = min(d[i][j], d[i-2][j-2] + l_cost);   // transposition
			}
		}
	}
	return d[l_string_length1][l_string_length2];
}

int countWords(string str){

	cout << "char* str " << str << endl;

	int numWords = 0;

	for(int i = 0; i < (int)str.length(); i++){

		cout << "char '" << str.at(i) << "'\n";

		if (str.at(i) == ' '){

			cout << "contei espaço\n";

			numWords++;
		}
	}
	numWords++;

	cout << "numero palavras " << numWords << endl;

	return numWords;
}

vector<string> exactSearch(string streetName, Graph<Local> &mapa){
	vector<string> result;

	for(int i = 0; i < mapa.getNumVertex(); i++){
		map<unsigned long long, string> localStreets = mapa.getVertexSet().at(i)->getInfo().getRoads();
		map<unsigned long long, string>::iterator it = localStreets.begin();
		map<unsigned long long, string>::iterator it_e = localStreets.end();
		while(it != it_e){

			string street = it->second;
			if(kmp(street, streetName) > 0){
				bool found = false;
				for(int j = 0; j < (int)result.size(); j++){
					if(street == result.at(j)){
						found = true;
					}
				}
				if(found == false){
					result.push_back(street);
				}
			}
			it++;
		}
	}
	return result;
}

vector<string> approximateSearch(string streetName, Graph<Local> &mapa){

	//TODO verificar se a pesquisa aproximada já dá resultados satisfatorios e testar com muitas coisas e no fim limpar os cout's todos daqui

	cout << "entrei\n";
	vector<string> result;

	map <string, float> matches;
	float max_dist = 0.0;

	do{

		cout << "teste1\n";

		max_dist += 5.0;

		for(int i = 0; i < mapa.getNumVertex(); i++){

			map<unsigned long long, string> localStreets = mapa.getVertexSet().at(i)->getInfo().getRoads();
			map<unsigned long long, string>::iterator it = localStreets.begin();

			while(it != localStreets.end()){

				string street = it->second;
				int dist = damerau_levenshtein_distance(street, streetName);

				cout << "strind street " << street << endl;

				//int nWords = countWords(street);
				int strLen = street.length();

				cout << "STRLEN!!! " << strLen << endl;

				float final_dist = dist/100/*strLen*/;		//TODO corrigir atribuiçao dos nomes às ruas para porder fazer aqui divisao por strLen
															//porque ha algumas que nao tem nome e dá zero, alem disso a fazer o cruzamentos
															//tmb nao vai funcionar porque os nomes estao todos mal
															//(se houver ruas que o ficheiro nas diz o nome tenho de por aqui um if para nao dividir por zero

				if( final_dist < max_dist){
					map<string, float>::iterator found = matches.find(street);
					if(found == matches.end()){
						matches.insert(pair<string, float>(street, final_dist));
					}
				}
				it++;
			}
		}

	}while(matches.size() == 0);

	float min = max_dist;
	string str;

	while(matches.size() > 0){

		cout << "teste2\n";

		map<string, float>::iterator ite = matches.begin();
		while(ite != matches.end()){

			if(ite->second <= min){
				min = ite->second;
				str = ite->first;
			}
			ite++;
		}

		result.push_back(str);
		matches.erase(matches.find(str));
		min = max_dist;
	}

	return result;
}
