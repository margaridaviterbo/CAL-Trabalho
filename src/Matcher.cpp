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

int kmp(string text, string pattern, double &time_spent_kmp, int &num_exec_kmp){

	clock_t begin = clock();

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

	clock_t end = clock();
	time_spent_kmp += ((double)(end - begin) / CLOCKS_PER_SEC)*pow(10, 3);
	num_exec_kmp++;

	return num;
}

int damerau_levenshtein_distance(string p_string1, string p_string2, double &time_spent_dld, int &num_exec_dld){

	clock_t begin = clock();

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

	clock_t end = clock();
	time_spent_dld += ((double)(end - begin) / CLOCKS_PER_SEC)*pow(10, 3);
	num_exec_dld++;

	return d[l_string_length1][l_string_length2];
}

int countWords(string str){
	int numWords = 0;

	for(int i = 0; i < (int)str.length(); i++){
		if (str.at(i) == ' '){
			numWords++;
		}
	}
	if(numWords > 0){
		numWords++;
	}

	return numWords;
}

vector<string> exactSearch(string streetName, Graph<Local> &mapa, double &time_spent_kmp, int &num_exec_kmp){
	vector<string> result;

	for(int i = 0; i < mapa.getNumVertex(); i++){
		map<unsigned long long, string> localStreets = mapa.getVertexSet().at(i)->getInfo().getRoads();
		map<unsigned long long, string>::iterator it = localStreets.begin();
		map<unsigned long long, string>::iterator it_e = localStreets.end();
		while(it != it_e){

			string street = it->second;
			if(kmp(street, streetName, time_spent_kmp, num_exec_kmp) > 0){
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

vector<string> approximateSearch(string streetName, Graph<Local> &mapa, double &time_spent_dld, int &num_exec_dld){

	vector<string> result;
	map <string, float> matches;
	float max_dist = 0.0;

	do{
		max_dist += 3;
		for(int i = 0; i < mapa.getNumVertex(); i++){

			map<unsigned long long, string> localStreets = mapa.getVertexSet().at(i)->getInfo().getRoads();
			map<unsigned long long, string>::iterator it = localStreets.begin();

			while(it != localStreets.end()){

				string street = it->second;
				int dist = damerau_levenshtein_distance(street, streetName, time_spent_dld, num_exec_dld);
				int strLen = countWords(street);

				float final_dist;

				if(strLen == 0){
					final_dist = 99999999999;	//nao entra nas matches
				}
				else{
					final_dist = dist/strLen;
				}

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

Local findCrossroad(vector<string> streets, Graph<Local> &mapa){

	bool found1, found2;
	Local local;

	for (int i = 0; i < mapa.getNumVertex(); i++){
		map<unsigned long long, string> roads = mapa.getVertexSet().at(i)->getInfo().getRoads();
		map<unsigned long long, string>::iterator it = roads.begin();

		found1 = false;
		found2 = false;
		while(it != roads.end()){
			if(it->second == streets.at(0)){
				found1 = true;
			}
			if(it->second == streets.at(1)){
				found2 = true;
			}
			it++;
		}
		if(found1 && found2){
			return mapa.getVertexSet().at(i)->getInfo();
		}
	}

	return Local(0, 0, pair<float, float> (0, 0), 0);

}
