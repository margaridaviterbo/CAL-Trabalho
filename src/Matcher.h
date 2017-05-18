#ifndef MATCHER_H_
#define MATCHER_H_

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <time.h>
#include <cmath>
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
 * @param time_spent_kmp acumula tempos de execuçao deste algoritmo
 * @param num_exec_kmp acumula numero de execuçoes  deste algoritmo
 */

int kmp(string text, string pattern, double &time_spent_kmp, int &num_exec_kmp);


/*
 * Algoritmo distancia de Damerau-Levenshtein para strings comparaçao de strings
 * @param p_string1 primeira string a comparar
 * @param p_string2 segunda string a comparar
 * @param time_spent_dld acumula tempos de execuçao deste algoritmo
 * @param num_exec_dld acumula numero de execuçoes  deste algoritmo
 */

int damerau_levenshtein_distance(string p_string1, string p_string2, double &time_spent_dld, int &num_exec_dld);


/**
 * função que conta o numero de palavras de uma string
 * @param str string cujas palavras serão contadas
 */

int countWords(string str);


/**
 * funçao que faz a pesquisa exata de uma rua no mapa
 * @param streetName nome da rua a pesquisar
 * @param mapa grafo onde pesquisar a rua
 * @param time_spent_kmp acumula tempos de execuçao deste algoritmo KMP
 * @param num_exec_kmp acula numero de execuçoes do algoritmo KMP
 */

vector<string> exactSearch(string streetName, Graph<Local> &mapa, double &time_spent_kmp, int &num_exec_kmp);


/**
 * funçao que faz a pesquisa aproximada de uma rua no mapa
 * @param streetName nome da rua a pesquisar
 * @param mapa grafo onde pesquisar a rua
 * @param time_spent_kmp acumula tempos de execuçao deste algoritmo distancia de Damerau-Levenshtein
 * @param num_exec_kmp acula numero de execuçoes do algoritmo Damerau-Levenshtein
 */

vector<string> approximateSearch(string streetName, Graph<Local> &mapa, double &time_spent_dld, int &num_exec_dld);


/**
 * funçao que testa se duas ruas se cruzam
 * @param streets contem duas ruas a testar cruzamento
 * @param mapa grafo onde pesquisar cruzamentos
 */

Local findCrossroad(vector<string> streets, Graph<Local> &mapa);

#endif /* MATCHER_H_ */
