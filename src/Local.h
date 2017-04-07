#ifndef Local_H
#define Local_H


#include <iostream>
#include <string>
#include <cmath>
#include <map>

using namespace std;

enum searchOptions {SHORTEST_DIST, SHORTEST_HEIGHT, CLOSEST, DIST_DISCOUNT, HEIGHT_DISCOUNT, BIGGEST_DISCOUNT};


/**
 * Classe que guarda toda a informação relativa a um local no mapa
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
	 * Função que devolve o atributo id
	 */
	unsigned long long getId() const;

	/**
	 * Função que devolve o atributo UXid
	 */
	int getUXid();

	/**
	 * Função que devolve o atributo coord
	 */
	pair<float, float> getCoordinates() const;

	/**
	 * Função que devolve a distancia do local ao centro da cidade
	 */
	float getDiffDistCenter() const;

	/**
	 * Função que devolve o atributo height
	 */
	float getHeight() const;

	/**
	 * Função que devolve a diferença de altura entre o local e o centro da cidade
	 */
	float getDiffHeightCenter() const;

	/**
	 * Função que devolve o peso da conexão entre dois locais
	 * @param nd representa o local de destino da conexão
	 * @param op representa a opção selecionada pelo user para o criterio de pesquisa de caminhos
	 */
	double getWeight(const Local nd, searchOptions op);

	/**
	 * funçao que devolve o parametro sharingPoint que é um pair que contem um boleano definindo ao nao o local como sharing point e caso seja o inteiro indica o numero de lugares disponiveis
	 */
	pair<bool, int> getSharingPoint();

	/**
	 * função que devolve um boleano indicando se o local é ou nao o sitio onde está o user
	 */
	bool getUserLocation();

	/**
	 * função que devolve um boleano indicando se o local é ou nao o centro da cidade
	 */
	bool getCityCenter();

	/**
	 * função que devolve o atributo roads que é um map que armazena o id da rua uma das ruas e o respetivo nome
	 */
	map<unsigned long long, string> getRoads();

	/**
	 * Operador de comparação de objetos Local
	 * @param nd é o local com o qual efetuar a comparação
	 */
	bool operator ==(const Local & nd);

	/**
	 * função que imprime as informações do local
	 */
	void print();

	/**
	 * função que atribui as informaçoes ao atributo sharingPoint
	 */
	void setSharingPoint(pair<bool, int> sp);

	/**
	 * função que atribui true ao atributo userLocation
	 */
	void setUserLocation();

	/**
	 * funçao que atribui true ao atributo city center
	 */
	void setCityCenter();

	/**
	 * funçao que atribui um valor ao atributo diffHeight
	 * @param diff é o valor a atribuir
	 */
	void setDiffHeightCenter(float diff);

	/**
	 * função que atribui um valor ao atributo diffDistCenter
	 * @param diff é o valor a atribuir
	 */
	void setDiffDistCenter(float diff);

	/**
	 * funçao que adiciona uma rua ao map roads
	 * @param road é a rua a adicionar
	 */
	void addRoad(pair<long long, string> road);

	/**
	 * funçao que atribui um nome a uma rua
	 * @param roadId é o identificador da rua à qual se vai adicionar o nome
	 * @param roadName é o nome a adicionar
	 */
	bool setRoadName(long long roadId, string roadName);
};


#endif Local_H	/* Local_H */
