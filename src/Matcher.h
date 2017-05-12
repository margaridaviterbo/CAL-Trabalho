#ifndef MATCHER_H_
#define MATCHER_H_

#include <iostream>
#include <string>
#include <vector>
#include "Graph.h"
#include "Local.h"

using namespace std;


/*
 * Inicializar funcao prefixo
 * @param patter padrao a pesquisar
 * @param prefix vetor a modificar
 */

void pre_kmp(string pattern, vector<int> & prefix);


/*
 * Algoritmo KMP para strings
 * @param text texto total onde encontrar padrao
 * @param pattern padrao a pesquisar
 * @return vezes encontradas
 */

int kmp(string text, string pattern);


vector<string> exactSearch(string streetName, Graph<Local> &map);	//TODO exactsearch (encontra rua) devolve todas as ruas que dêm match ou diz que nao tem

vector<string> approximateSearch();		//TODO approximate search (encontra rua) devolve as ruas parecidas ordenadas por similaridade

string findCrossroad(string street1, string street2);	//TODO findcrossroad (encontra cruzamento entre as duas ruas e se tiver vê se tem sharing point e devolve string a informar destas duas cenas

#endif /* MATCHER_H_ */
