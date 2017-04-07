#ifndef Local_H
#define Local_H


#include <iostream>
#include <string>
#include <cmath>
#include <map>

using namespace std;

enum searchOptions {SHORTEST_DIST, SHORTEST_HEIGHT, CLOSEST, DIST_DISCOUNT, HEIGHT_DISCOUNT, BIGGEST_DISCOUNT};


/**
 * Classe que guarda toda a informa��o relativa a um local no mapa
 */
class Local{
private:
	int UXid;
	unsigned long long id;
	pair<float, float> coordinates;		//latitude, longitude
	float diffDistCenter;
	float height = 0;
	float diffHeightCenter = 0;
	map<unsigned long long, string> roads;		//idRoad, roadName
	pair<bool, int> sharingPoint = pair<bool, int>(false, 0);	// is/is not sharingpoint, spots available
	bool userLocation = false;
	bool cityCenter = false;
public:
	Local(){};

	/**
	 * Construtor que cria uma instancia de Local
	 * @param id identifica o local com o id do ficheiro de origem
	 * @param UXid identifica o local com um numero sequencial
	 * @param coord guarda as coordenadas (latitude, longitude) do local
	 * @param height guarda a altura do local
	 */
	Local(unsigned long long id, int UXid, pair<float, float> coord, float height);

	/**
	 * Fun��o que devolve o atributo id
	 */
	unsigned long long getId() const;

	/**
	 * Fun��o que devolve o atributo UXid
	 */
	int getUXid();

	/**
	 * Fun��o que devolve o atributo coord
	 */
	pair<float, float> getCoordinates() const;

	/**
	 * Fun��o que devolve a distancia do local ao centro da cidade
	 */
	float getDiffDistCenter() const;

	/**
	 * Fun��o que devolve o atributo height
	 */
	float getHeight() const;

	/**
	 * Fun��o que devolve a diferen�a de altura entre o local e o centro da cidade
	 */
	float getDiffHeightCenter() const;

	/**
	 * Fun��o que devolve o peso da conex�o entre dois locais
	 * @param nd representa o local de destino da conex�o
	 * @param op representa a op��o selecionada pelo user para o criterio de pesquisa de caminhos
	 */
	double getWeight(const Local nd, searchOptions op);

	/**
	 * fun�ao que devolve o parametro sharingPoint que � um pair que contem um boleano definindo ao nao o local como sharing point e caso seja o inteiro indica o numero de lugares disponiveis
	 */
	pair<bool, int> getSharingPoint();

	/**
	 * fun��o que devolve um boleano indicando se o local � ou nao o sitio onde est� o user
	 */
	bool getUserLocation();

	/**
	 * fun��o que devolve um boleano indicando se o local � ou nao o centro da cidade
	 */
	bool getCityCenter();

	/**
	 * fun��o que devolve o atributo roads que � um map que armazena o id da rua uma das ruas e o respetivo nome
	 */
	map<unsigned long long, string> getRoads();

	/**
	 * Operador de compara��o de objetos Local
	 * @param nd � o local com o qual efetuar a compara��o
	 */
	bool operator ==(const Local & nd);

	/**
	 * fun��o que imprime as informa��es do local
	 */
	void print();

	/**
	 * fun��o que atribui as informa�oes ao atributo sharingPoint
	 */
	void setSharingPoint(pair<bool, int> sp);

	/**
	 * fun��o que atribui true ao atributo userLocation
	 */
	void setUserLocation();

	/**
	 * fun�ao que atribui true ao atributo city center
	 */
	void setCityCenter();

	/**
	 * fun�ao que atribui um valor ao atributo diffHeight
	 * @param diff � o valor a atribuir
	 */
	void setDiffHeightCenter(float diff);

	/**
	 * fun��o que atribui um valor ao atributo diffDistCenter
	 * @param diff � o valor a atribuir
	 */
	void setDiffDistCenter(float diff);

	/**
	 * fun�ao que adiciona uma rua ao map roads
	 * @param road � a rua a adicionar
	 */
	void addRoad(pair<long long, string> road);

	/**
	 * fun�ao que atribui um nome a uma rua
	 * @param roadId � o identificador da rua � qual se vai adicionar o nome
	 * @param roadName � o nome a adicionar
	 */
	bool setRoadName(long long roadId, string roadName);
};


#endif Local_H	/* Local_H */
