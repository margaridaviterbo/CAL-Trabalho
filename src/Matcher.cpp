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

vector<string> exactSearch(string streetName, Graph<Local> &mapa){
	vector<string> result;

	for(int i = 0; i < mapa.getNumVertex(); i++){
		map<unsigned long long, string> localStreets = mapa.getVertexSet().at(i)->getInfo().getRoads();
		map<unsigned long long, string>::iterator it = localStreets.begin();
		map<unsigned long long, string>::iterator it_e = localStreets.end();
		while(it != it_e){
			string street = it->second;
			if(kmp(street ,streetName) > 0){
				bool found = false;
				for(int j = 0; j < result.size(); j++){
					if(street == result.at(j)){
						found = true;
					}
					if(found == false){
						result.push_back(street);
					}
				}
			}
		}
	}

	return result;
}

vector<string> approximateSearch(){
	vector<string> v;
	return v;
}
