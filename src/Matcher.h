#ifndef MATCHER_H_
#define MATCHER_H_

#include <iostream>
#include <string>
#include <vector>
#include <map>
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

int damerau_levenshtein_distance(string p_string1, string p_string2);

int countWords(string str);

vector<string> exactSearch(string streetName, Graph<Local> &mapa);

vector<string> approximateSearch(string streetName, Graph<Local> &mapa);

Local findCrossroad(string street1, string street2);

#endif /* MATCHER_H_ */
