#include <iostream>

#include "Graph.h"
#include "MenusManager.h"
#include "Parsers.h"
#include <vector>
#include "Local.h"
#include "graphviewer.h"
#include "utils.h"
#include "Matcher.h"
using namespace std;


//TODO ver o que � preciso fazer para
//Avalie a complexidade (te�rica e empiricamente) dos algoritmos implementados em fun��o dos dados de input usados.

/*
 *  estenda o trabalho realizado com funcionalidades apropriadas que permitem a consulta da exist�ncia ou n�o de um ponto (recolha ou entrega)
 *  num determinado cruzamento entre ruas. Implemente esta funcionalidade, considerando tanto pesquisa exata, assim como pesquisa aproximada,
 *  das strings identificativas dos nomes das ruas fornecidas. Para pesquisa exata, caso os nomes de rua n�o existam,
 *  dever� retornar mensagem de lugar desconhecido. Para a pesquisa aproximada, dever� retornar os nomes de ruas mais pr�ximos,
 *  ordenados por similaridade, onde poder� haver um ponto (recolha ou entrega).
 * */


int main(){


	cout << kmp("Travessa Fernando Namora", "Fernando");

	/*

	int city;

	cout << "\n\n\t\t\t\tWelcome to this BikeSharing Platform!\n\n";
	cout << "\t\t\t\t   Chose one of the following cities:\n";
	cout << "\t\t\t\t\t1 - SmallLand\n";
	cout << "\t\t\t\t\t2 - MediumLand\n";
	cout << "\t\t\t\t\t3 - Bigland\n";
	cout << "\n\t\t\t\t\tCITY: ";
	cin >> city;

	while(city < 1 || city > 3){
		cout << "\n\nInvalid city, try again: ";
		cin >> city;
	}
	cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
	displayMainMenu(city);

	*/

	return 0;
}
