/*
 * Graph.h
 */
#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <queue>
#include <algorithm>
#include <limits.h>
using namespace std;

const int INT_INFINITY = INT_MAX;

template <class T> class Edge;
template <class T> class Graph;

template <class T>

/**
 * Classe que armazena informaçao sobre os vertices usados no grafo
 */
class Vertex {
	T info;
	vector<Edge<T>  > adj;
	bool visited;
	bool processed;
	double dist;
	void addEdge(Vertex<T> *dest, double w);
	bool removeEdgeTo(Vertex<T> *d);
public:
	/**
	 * Construtor que cria um vértice de um grafo
	 * @param info guarda o objeto alojado no vertice
	 * @param adj guarda todas as conexões do vertice com outros vertices
	 * @param visited  usado na pesquisa de caminhos
	 * @param processed usado na pesquisa de caminhos
	 * @param dist usado na pesquisa de caminhos
	 */
	Vertex(T in);

	friend class Graph<T>;

	/**
	 * Função que devolve o atributo dist
	 */
	double getDist() const;

	/**
	 * Função que devolve o atributo info
	 */
	T getInfo();

	/**
	 * Função que devolve o atributo adj
	 */
	vector<Edge<T> > getAdj();

	/**
	 * @param publico usado na criaçao de caminhos
	 */
	Vertex* prev;
};

template<class T>
T Vertex<T>::getInfo(){
	return info;
}

template<class T>
vector<Edge<T>  > Vertex<T>::getAdj(){
	return adj;
}

template <class T>
bool Vertex<T>::removeEdgeTo(Vertex<T> *d) {
	typename vector<Edge<T> >::iterator it= adj.begin();
	typename vector<Edge<T> >::iterator ite= adj.end();
	while (it!=ite) {
		if (it->dest == d) {
			adj.erase(it);
			return true;
		}
		else it++;
	}
	return false;
}

template <class T>
Vertex<T>::Vertex(T in): info(in), visited(false){}

template <class T>
double Vertex<T>::getDist() const {
	return this->dist;
}

template <class T>
void Vertex<T>::addEdge(Vertex<T> *dest, double w) {
	Edge<T> edgeD(dest,w);
	adj.push_back(edgeD);
}

template <class T>

/**
 * Classe que guarda a informaçao sobre as conexões do grafo
 */
class Edge {
	Vertex<T> * dest;
	double weight;
public:

	/**
	 * construtor que cria um edge que liga dois vertices
	 * @param d guarda o vertice de destino da ligação
	 * @param w guarda o peso da aresta
	 */
	Edge(Vertex<T> *d, double w);

	/**
	 * Função que devolve o atributo weight
	 */
	double getWeight();

	/**
	 * Função que devolve o atributo dest
	 */
	Vertex<T>* getDest();

	friend class Graph<T>;
	friend class Vertex<T>;
};

template <class T>
Edge<T>::Edge(Vertex<T> *d, double w): dest(d), weight(w){}

template <class T>
double Edge<T>::getWeight(){
	return weight;
}

template <class T>
Vertex<T>* Edge<T>::getDest(){
	return dest;
}

template <class T>

/**
 * Classe que cria e guarda informaçoes de grafos
 */
class Graph {
	vector<Vertex<T> *> vertexSet;
	void dfs(Vertex<T> *v, vector<T> &res) const;
public:

	/**
	 * Função que adiciona um vertice ao grafo
	 * @param in guarda o objeto a inserir no vertice
	 */
	bool addVertex(const T &in);

	/**
	 * Função que adiciona uma conexao ao grafo
	 * @param sourc guarda o vertice onde começa a aresta
	 * @param dest guarda o vertive onde acaba a aresta
	 * @param w guarda o peso da aresta
	 */
	bool addEdge(const T &sourc, const T &dest, double w);

	/**
	 * Função que remove um vertice do grafo
	 * @param in guarda informaçao do objeto alojado no vertice a eliminar
	 */
	bool removeVertex(const T &in);

	/**
	 * Função que devolve vertice procurado
	 * @param in guarda o objeto a procurar nos vertices do grafo
	 */
	Vertex<T>* getVertex(const T &in);

	/**
	 * Funçao que procura e devolve um objeto guardado num vertice
	 * @param id quarda o id do objeto a procurar
	 */
	T* getLocal(unsigned long long id);

	/**
	 * Funçao que procura e devolve um objeto guardado num vertice
	 * @param lat quarda a latitude do objeto a procurar
	 */
	T* getLocal(double lat);

	/**
	 * Funçao que procura e devolve um objeto guardado num vertice
	 * @param id quarda a posiçao no vetor de vertices do vertice a procurar
	 */
	T* getLocal(int i);

	/**
	 * Função que elimina uma conexão entre dois vertices do grafo
	 * @param sourc guarda objeto do primeiro vertice da ligaçao
	 * @param dest guarda informaçao do segundo vertice da ligaçao
	 */
	bool removeEdge(const T &sourc, const T &dest);

	/**
	 * Função que faz pesquisa em profundidade no grafo
	 */
	vector<T> dfs() const;

	/**
	 * funçao que faz pesquisa em largura no grafo
	 */
	vector<T> bfs(Vertex<T> *v) const;

	int maxNewChildren(Vertex<T> *v, T &inf) const;

	/**
	 * Função que devolve o vetor de todos os vertices do grafo
	 */
	vector<Vertex<T> * > getVertexSet() const;

	/**
	 *Função que devolve o numero de vertices do grafo
	 */
	int getNumVertex() const;

	/**
	 * Funçao que implementa o algoritmo de Dijkstra
	 * @param s objeto alojado no vertice de partida para procurar caminho
	 */
	void dijkstraShortestPath(const T &s);

	/**
	 * Função que encontra caminho mais curto entre dois vertices usando o algoritmo de Dijkstra
	 * @param lc objeto alojado no vertice de partida para procurar caminho
	 * @param op inteiro que define a forma de pesquisa do caminho mais curto
	 */
	vector<int> findShortestPath(T lc, int op);

	/**
	 * Função que devolve vetor de objetos alojados nos vertices que fazem parte do caminho encontrado
	 * @param dest vertice de destino
	 */
	vector<T> getPath(Vertex<T> *dest);
};

template <class T>
int Graph<T>::getNumVertex() const {
	return vertexSet.size();
}
template <class T>
vector<Vertex<T> * > Graph<T>::getVertexSet() const {
	return vertexSet;
}

template <class T>
bool Graph<T>::addVertex(const T &in) {
	typename vector<Vertex<T>*>::iterator it= vertexSet.begin();
	typename vector<Vertex<T>*>::iterator ite= vertexSet.end();
	for (; it!=ite; it++)
		if ((*it)->info == in) return false;
	Vertex<T> *v1 = new Vertex<T>(in);
	vertexSet.push_back(v1);
	return true;
}

template <class T>
bool Graph<T>::removeVertex(const T &in) {
	typename vector<Vertex<T>*>::iterator it= vertexSet.begin();
	typename vector<Vertex<T>*>::iterator ite= vertexSet.end();
	for (; it!=ite; it++) {
		if ((*it)->info == in) {
			Vertex<T> * v= *it;
			vertexSet.erase(it);
			typename vector<Vertex<T>*>::iterator it1= vertexSet.begin();
			typename vector<Vertex<T>*>::iterator it1e= vertexSet.end();
			for (; it1!=it1e; it1++) {
				(*it1)->removeEdgeTo(v);
			}
			delete v;
			return true;
		}
	}
	return false;
}

template <class T>
Vertex<T>* Graph<T>::getVertex(const T &in){
	typename vector<Vertex<T>*>::iterator it= vertexSet.begin();
	typename vector<Vertex<T>*>::iterator ite= vertexSet.end();
	for (; it!=ite; it++) {
		if ((*it)->info == in) {
			Vertex<T> *v= *it;
			return v;
		}
	}
}

template <class T>
T* Graph<T>::getLocal(unsigned long long id){
	typename vector<Vertex<T>*>::iterator it= vertexSet.begin();
	typename vector<Vertex<T>*>::iterator ite= vertexSet.end();
	for (; it!=ite; it++) {
		if (((*it)->info).getId() == id) {
			return &((*it)->info);
		}
	}
}

template <class T>
T* Graph<T>::getLocal(double lat){
	typename vector<Vertex<T>*>::iterator it= vertexSet.begin();
	typename vector<Vertex<T>*>::iterator ite= vertexSet.end();
	for (; it!=ite; it++) {
		if (((*it)->info).getCoordinates().first == lat) {
			return &((*it)->info);
		}
	}
	return NULL;
}

template <class T>
T* Graph<T>::getLocal(int i) {
	typename vector<Vertex<T>*>::iterator it = vertexSet.begin();
	int count = 0;
	while (count < i) {
		it++;
		count++;
	}
	return &((*it)->info);
}

template <class T>
bool Graph<T>::addEdge(const T &sourc, const T &dest, double w) {
	typename vector<Vertex<T>*>::iterator it= vertexSet.begin();
	typename vector<Vertex<T>*>::iterator ite= vertexSet.end();
	int found=0;
	Vertex<T> *vS, *vD;
	while (found!=2 && it!=ite ) {
		if ( (*it)->info == sourc )
		{ vS=*it; found++;}
		if ( (*it)->info == dest )
		{ vD=*it; found++;}
		it ++;
	}
	if (found!=2) return false;
	vS->addEdge(vD,w);
	return true;
}

template <class T>
bool Graph<T>::removeEdge(const T &sourc, const T &dest) {
	typename vector<Vertex<T>*>::iterator it= vertexSet.begin();
	typename vector<Vertex<T>*>::iterator ite= vertexSet.end();
	int found=0;
	Vertex<T> *vS, *vD;
	while (found!=2 && it!=ite ) {
		if ( (*it)->info == sourc )
		{ vS=*it; found++;}
		if ( (*it)->info == dest )
		{ vD=*it; found++;}
		it ++;
	}
	if (found!=2) return false;
	return vS->removeEdgeTo(vD);
}




template <class T>
vector<T> Graph<T>::dfs() const {
	typename vector<Vertex<T>*>::const_iterator it= vertexSet.begin();
	typename vector<Vertex<T>*>::const_iterator ite= vertexSet.end();
	for (; it !=ite; it++)
		(*it)->visited=false;
	vector<T> res;
	it=vertexSet.begin();
	for (; it !=ite; it++)
		if ( (*it)->visited==false )
			dfs(*it,res);
	return res;
}

template <class T>
void Graph<T>::dfs(Vertex<T> *v,vector<T> &res) const {
	v->visited = true;
	res.push_back(v->info);
	typename vector<Edge<T> >::iterator it= (v->adj).begin();
	typename vector<Edge<T> >::iterator ite= (v->adj).end();
	for (; it !=ite; it++)
		if ( it->dest->visited == false )
			dfs(it->dest, res);
}

template <class T>
vector<T> Graph<T>::bfs(Vertex<T> *v) const {
	vector<T> res;
	queue<Vertex<T> *> q;
	q.push(v);
	v->visited = true;
	while (!q.empty()) {
		Vertex<T> *v1 = q.front();
		q.pop();
		res.push_back(v1->info);
		typename vector<Edge<T> >::iterator it=v1->adj.begin();
		typename vector<Edge<T> >::iterator ite=v1->adj.end();
		for (; it!=ite; it++) {
			Vertex<T> *d = it->dest;
			if (d->visited==false) {
				d->visited=true;
				q.push(d);
			}
		}
	}
	return res;
}

template <class T>
int Graph<T>::maxNewChildren(Vertex<T> *v, T &inf) const {
	vector<T> res;
	queue<Vertex<T> *> q;
	queue<int> level;
	int maxChildren=0;
	inf =v->info;
	q.push(v);
	level.push(0);
	v->visited = true;
	while (!q.empty()) {
		Vertex<T> *v1 = q.front();
		q.pop();
		res.push_back(v1->info);
		int l=level.front();
		level.pop(); l++;
		int nChildren=0;
		typename vector<Edge<T> >::iterator it=v1->adj.begin();
		typename vector<Edge<T> >::iterator ite=v1->adj.end();
		for (; it!=ite; it++) {
			Vertex<T> *d = it->dest;
			if (d->visited==false) {
				d->visited=true;
				q.push(d);
				level.push(l);
				nChildren++;
			}
		}
		if (nChildren>maxChildren) {
			maxChildren=nChildren;
			inf = v1->info;
		}
	}
	return maxChildren;
}

template <class T>
struct vertex_greater_than {
	bool operator()(Vertex<T> * a, Vertex<T> * b) const {
		return a->getDist() > b->getDist();
	}
};

template<class T>
void Graph<T>::dijkstraShortestPath(const T &s) {

	for(unsigned int i = 0; i < vertexSet.size(); i++) {
		vertexSet[i]->prev = NULL;
		vertexSet[i]->dist = INT_INFINITY;
		vertexSet[i]->processed = false;
	}

	Vertex<T>* v = getVertex(s);
	v->dist = 0;

	vector< Vertex<T>* > visitedVertexes;
	visitedVertexes.push_back(v);

	make_heap(visitedVertexes.begin(), visitedVertexes.end());


	while( !visitedVertexes.empty() ) {

		v = visitedVertexes.front();
		pop_heap(visitedVertexes.begin(), visitedVertexes.end());
		visitedVertexes.pop_back();

		for(unsigned int i = 0; i < v->adj.size(); i++) {
			Vertex<T>* w = v->adj[i].dest;

			if(v->dist + v->adj[i].weight < w->dist ) {

				w->dist = v->dist + v->adj[i].weight;
				w->prev = v;

				if(!w->processed)
				{
					w->processed = true;
					visitedVertexes.push_back(w);
				}

				make_heap(visitedVertexes.begin(),visitedVertexes.end(),vertex_greater_than<T>());
			}
		}
	}
}

template<class T>
vector<int> Graph<T>::findShortestPath(T lc, int op){
	dijkstraShortestPath(lc);

	int dest = -1;

	if(op == 1 || op == 2 || op == 3){
		float min = 123871;
		int id = -1;
		size_t j;
		for(j = 0; j < getVertexSet().size(); j++){
			if(getVertexSet().at(j)->getInfo().getSharingPoint().first && (getVertexSet().at(j)->getInfo().getSharingPoint().second > 0) && getVertexSet().at(j)->getDist() < min) {
				min = getVertexSet().at(j)->getDist();
				id = getVertexSet().at(j)->getInfo().getId();
				dest = j;
			}
		}
	}

	if(op == 4 || op == 5 || op == 6){
		float max = 0;
		int id = -1;
		size_t j;
		for(j = 0; j < getVertexSet().size(); j++){
			if(getVertexSet().at(j)->getInfo().getSharingPoint().first && (getVertexSet().at(j)->getInfo().getSharingPoint().second > 0) && getVertexSet().at(j)->getDist() > max) {
				max = getVertexSet().at(j)->getDist();
				id = getVertexSet().at(j)->getInfo().getId();
				dest = j;
			}
		}
	}

	vector<int> path;
	cout << getPath(getVertexSet().at(dest)).at(0).getUXid();
	for(size_t i=1; i < getPath(getVertexSet().at(dest)).size(); i++) {
		cout << "  ==>  " << getPath(getVertexSet().at(dest)).at(i).getUXid();
		path.push_back(getPath(getVertexSet().at(dest)).at(i).getUXid());
	}
	return path;
}


template<class T>
vector<T> Graph<T>::getPath(Vertex<T> *dest){
	vector<T> path;
	path.push_back(dest->info);

	while(dest->prev != NULL){
		dest = dest->prev;
		path.push_back(dest->info);
	}

	reverse(path.begin(), path.end());
	return path;
}


#endif /* GRAPH_H_ */
